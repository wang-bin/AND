/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#include "surface_texture_p.hpp"
#include "surface_texture_jni.hpp"
#include "android.graphics.SurfaceTexture.hpp"

#pragma comment(lib, "libandroid.so")

#include <iostream>
#include <utility>
using namespace std;
namespace ndk {
namespace android {

static bool use_ndk = true;

bool isASurfaceTextureNdk()
{
	if (__builtin_available(android 28, *)) {
		return use_ndk;
	}
	return false;
}

void setASurfaceTextureNdk(bool value)
{
	use_ndk = value;
}

static bool isSurfaceTexture(JNIEnv* env, jobject obj)
{
	static const jclass cls = [env]() -> jclass {
			if (auto local = jmi::LocalRef(env->FindClass("android/graphics/SurfaceTexture"), env))
			    return static_cast<jclass>(env->NewGlobalRef(local));
			return nullptr;
		}();
	if (!cls)
		return false;
	return env->IsInstanceOf(obj, cls);
}

ASurfaceTexture* ASurfaceTexture_fromSurfaceTexture(JNIEnv* env, jobject surfacetexture)
{
	if (isASurfaceTextureNdk()) {
		if (__builtin_available(android 28, *)) {
			clog << "ndk ASurfaceTexture_fromSurfaceTexture" << endl;
			return fromNdk(::ASurfaceTexture_fromSurfaceTexture(env, surfacetexture));
		}
	}

	clog << "jni ASurfaceTexture_fromSurfaceTexture" << endl;
	if (!env || !surfacetexture)
		return nullptr;
	if (!isSurfaceTexture(env, surfacetexture))
		return nullptr;

	jmi::android::graphics::SurfaceTexture st(surfacetexture, false);
	if (!st) {
		std::clog << __PRETTY_FUNCTION__ << " ERROR: failed to wrap SurfaceTexture" << std::endl;
		return nullptr;
	}
	return fromJmi(std::move(st));
}

} // namespace android
} // namespace ndk
