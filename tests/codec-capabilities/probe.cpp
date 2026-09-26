#include "ndk/media/NdkMediaCodecInfoPriv.hpp"
#include "ndk/media/NdkMedia.h"
#include <atomic>
#include <thread>
#include <vector>

// Host-only dependencies: force the real NdkMediaCodecInfo.cpp Java fallback.
namespace ndk {
void* mediandk_so() { return nullptr; }
const jmi::android::media::MediaFormat& toJmi(const AMediaFormat*) {
    static const jmi::android::media::MediaFormat unused;
    return unused;
}
AMediaFormat* toNdk(const AMediaFormat* format) {
    return const_cast<AMediaFormat*>(format);
}
}

extern "C" JNIEXPORT void JNICALL
Java_CodecCapabilitiesTest_probe(JNIEnv* env, jclass, jobject codec, jboolean warm) {
    JavaVM* vm = nullptr;
    env->GetJavaVM(&vm);
    jmi::javaVM(vm);
    ndk::AMediaCodecInfo info;
    info.jni_.reset(codec, env);
    info.media_type_ = "video/avc";
    const ndk::ACodecVideoCapabilities* initial = nullptr;
    if ((warm && ndk::AMediaCodecInfo_getVideoCapabilities(&info, &initial) != ndk::AMEDIA_OK) ||
        ndk::AMediaCodecInfo_getVideoCapabilities(&info, nullptr) != ndk::AMEDIA_ERROR_INVALID_PARAMETER ||
        ndk::ACodecVideoCapabilities_areSizeAndRateSupported(nullptr, 1920, 1080, 30) != -1) {
        env->ThrowNew(env->FindClass("java/lang/AssertionError"), "invalid parameter behavior changed");
        return;
    }
    std::atomic<bool> start{false};
    std::atomic<int> failures{0};
    std::vector<std::thread> workers;
    for (int worker = 0; worker < 8; ++worker) {
        workers.emplace_back([&] {
            while (!start.load(std::memory_order_acquire))
                std::this_thread::yield();
            for (int i = 0; i < 2000; ++i) {
                const ndk::ACodecVideoCapabilities* caps = nullptr;
                if (ndk::AMediaCodecInfo_getVideoCapabilities(&info, &caps) != ndk::AMEDIA_OK ||
                    ndk::ACodecVideoCapabilities_areSizeAndRateSupported(caps, 1920, 1080, 30) != 1) {
                    ++failures;
                    break;
                }
                // A previously returned pointer must remain valid after re-probing.
                if ((initial && caps != initial) ||
                    ndk::ACodecVideoCapabilities_areSizeAndRateSupported(initial ? initial : caps, 640, 480, 30) != 0)
                    ++failures;
                if (i == 1 &&
                    ndk::ACodecVideoCapabilities_areSizeAndRateSupported(caps, -1, 1080, 30) != -1)
                    ++failures;
            }
        });
    }
    start.store(true, std::memory_order_release);
    for (auto& worker : workers)
        worker.join();
    if (failures.load()) {
        env->ThrowNew(env->FindClass("java/lang/AssertionError"), "capability queries failed");
        return;
    }
}
