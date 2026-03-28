# Android Native Dev in Modern C++

## Directories:

- classes: C++ classes for java implemented in [JMI](https://github.com/wang-bin/JMI)
- ndk/media: libmediandk APIs(requires api level 21+) implemented for all api levels. Either use libmediandk C api directly or use JMI classes, controlled by user at runtime
- ndk/aaudio: compatibile with target < 26 without code change

## NDK Directory Design

### CMake Targets

The `ndk/` subdirectory provides two CMake targets whose names intentionally match the corresponding Android NDK shared libraries: `mediandk` (for `libmediandk.so`) and `aaudio` (for `libaaudio.so`). This naming means a consuming project can write `target_link_libraries(myapp mediandk)` and link against the compatibility OBJECT target rather than the raw system library. The system library (`-lmediandk`, etc.) is added as a `PRIVATE` dependency of the target so consumers don't need to mention it separately.

Both targets are declared as `OBJECT` libraries (not `STATIC`):

- **`mediandk`**: Implements `libmediandk` APIs. When the target Android API level is ≥ 21, the build links against `libmediandk.so` (`-lmediandk`) so that weak-symbol APIs introduced after API 21 resolve from the system library at link time. When targeting API < 21, the extra source files `NdkImage.cpp` and `NdkImageReader.cpp` are compiled in, providing pure-dlsym stubs for those APIs.
- **`aaudio`**: Implements `libaaudio` APIs. Only built when the target Android API level is < 26 (when `libaaudio.so` is unavailable). Always links against `dl` for `dlsym`.

**Why `OBJECT` instead of `STATIC`?** Weak symbols must remain unresolved until the final link step so that the linker can resolve them against the real symbols from the platform libraries (e.g. `AImageReader` APIs added to `libmediandk.so` on API 26+). When a `STATIC` archive is linked, the linker may bind a weak symbol to the weak definition found in the archive rather than searching further for a strong definition in another library. Using `OBJECT` libraries preserves each object file individually so the final link sees all symbols together and resolves weak definitions against strong ones correctly.

**Build dependencies**: The `mediandk` target `PUBLIC`-links `android_classes` (which in turn `PUBLIC`-links `jmi`). Any target that links `mediandk` therefore automatically gets both `android_classes` and `jmi` without having to name them explicitly. The system library (`-lmediandk`, `dl`) is always `PRIVATE` to avoid leaking that dependency to consumers.

### Android API Level Macro Guards

Source files use `(__ANDROID_API__ + 0)` to guard code blocks that depend on a minimum API level:

```c
#if (__ANDROID_API__ + 0) >= 21
// code that requires API 21 or higher
#endif

#if (__ANDROID_API__ + 0) < 26
// compatibility code for targets below API 26
#endif
```

The `+ 0` idiom ensures safe evaluation when `__ANDROID_API__` is undefined (it evaluates to 0 rather than a preprocessor error).

NDK version guards use the same idiom:

```c
#if (__NDK_MAJOR__ + 0) >= 28
// APIs only available in NDK 28+
#endif
```

### When to Use Weak Symbol Only

There are two ways to get weak symbols in this codebase:

**1. Explicit `__attribute__((weak))`**: Use this when you need to declare a symbol from a linked library that may or may not be present on the running device, and you do not want to use `dlsym`. This also prevents duplicate-symbol linker errors when the same object appears in multiple modules.

Example from `ndk/media/NdkMediaCodec.cpp`:

```c
// null if not present in the linked libandroid.so (pre-API 26 devices)
extern "C" jobject ANativeWindow_toSurface(JNIEnv* env, ANativeWindow* window) __attribute__((weak));
```

Check the pointer at runtime before calling:

```c
if (ANativeWindow_toSurface) {
    s.reset(ANativeWindow_toSurface(env, anw), env);
}
```

**2. Availability attributes from NDK headers**: When using NDK 23+ and the compiler defines `__ANDROID_UNAVAILABLE_SYMBOLS_ARE_WEAK__`, API functions in the NDK headers that are annotated with availability macros are marked as weak symbols by the compiler — no manual `__attribute__((weak))` is needed. Use `__builtin_available()` to guard the call at runtime:

```c
#if defined(__ANDROID_UNAVAILABLE_SYMBOLS_ARE_WEAK__) && (__NDK_MAJOR__ + 0) >= 23
    if (__builtin_available(android 26, *)) {
        s.reset(ANativeWindow_toSurface(env, anw), env);
    }
#else
    // fall back to manual dlsym
#endif
```

### fromNdk() / toNdk() — Pointer Wrapping

Because the project re-declares API types such as `AMediaCodec` and `AMediaCodecInfo` inside `NDKMEDIA_NS`, these wrapper structs and the identically-named opaque types in the system `libmediandk.so` are **different, incompatible types**. The system library functions expect the system's own opaque pointers; the project's functions expose the project's wrapper pointers to callers.

`fromNdk()` and `toNdk()` bridge this gap:

- **`fromNdk(SystemType* p)`** — allocates a new project wrapper struct on the heap, stores the system pointer in `ndk_`, and returns a pointer to the wrapper. Used whenever the system library returns a new object that must be handed to the caller as the project's type.
- **`toNdk(const WrapperType* p)`** — extracts the stored `ndk_` system pointer from the wrapper and returns it. Used to unwrap before passing an object to a system library function that expects its own opaque type.

Example from `NdkMediaCodec.cpp`:

```c
// The project's own wrapper struct (NDKMEDIA_NS)
struct AMediaCodec {
    AMediaCodec* ndk_;   // pointer to the REAL system AMediaCodec opaque struct
    android::media::MediaCodec jni_;  // JMI fallback
    ...
};

AMediaCodec* fromNdk(AMediaCodec* obj) {
    if (!obj) return nullptr;
    return new AMediaCodec{obj};  // wrap system pointer
}

AMediaCodec* toNdk(const AMediaCodec* obj) {
    if (!obj) return nullptr;
    return obj->ndk_;              // unwrap to system pointer
}

// Usage in an API function:
AMediaCodec* AMediaCodec_createCodecByName(const char* name) {
    auto so = mediandk_so();
    if (so) {
        static const auto fp = (decltype(&AMediaCodec_createCodecByName))dlsym(so, __func__);
        return fromNdk(fp(name));  // system returns system ptr → wrap it
    }
    // JMI fallback ...
}

media_status_t AMediaCodec_delete(AMediaCodec* obj) {
    auto so = mediandk_so();
    if (so) {
        static const auto fp = (decltype(&AMediaCodec_delete))dlsym(so, __func__);
        auto ret = fp(obj->ndk_);  // pass system ptr directly, then delete the wrapper
        delete obj;
        return ret;
    }
    // JMI fallback ...
}
```

The same `fromNdk`/`toNdk` pair is defined for every wrapped type (`AMediaFormat`, `AMediaCrypto`, `AMediaCodecInfo`, `ACodecAudioCapabilities`, etc.) so the same pattern applies everywhere.

### When to Use dlsym

The approach depends on whether the API has a Java/JMI equivalent:

**Case 1 — API has a JMI fallback (corresponding Java class exists)**

Add the NDK types and API declarations to the project's own namespace (`NDKMEDIA_NS`). The internal struct wraps both the native NDK pointer (`ndk_`) and a JMI object (`jni_`). At runtime, prefer the function pointer obtained via `dlsym`; if resolution fails, fall back to the JMI implementation:

```c
// Inside NDKMEDIA_NS
struct AMediaCodecInfo {
    const AMediaCodecInfo* ndk_ = nullptr;               // native NDK pointer (if available)
    jmi::android::media::MediaCodecInfo jni_;            // JMI fallback
    ...
};

const char* AMediaCodecInfo_getCanonicalName(const AMediaCodecInfo* info) {
    static const auto fp = (decltype(&AMediaCodecInfo_getCanonicalName))
        (mediandk_so() ? dlsym(mediandk_so(), __func__) : nullptr);
    if (fp)
        return fp(toNdk(info));  // NDK path: toNdk unwraps to the native pointer
    // JMI fallback (const_cast is safe: canonical_name_ is a lazily-cached mutable field):
    auto obj = const_cast<AMediaCodecInfo*>(info);
    obj->canonical_name_ = obj->jni_.getCanonicalName();
    return strOrNull(obj->canonical_name_);
}
```

**Case 2 — API has no JMI fallback (no corresponding Java class)**

Implement the C API in the global namespace (or in a file-level anonymous namespace for helpers), guarded by the Android API level macro so the file is only compiled when the system library is not available. `NDKCOMPAT_DEFINE_RET` / `NDKCOMPAT_DEFINE_VOID` from `NdkCompatAPI.h` generate these stubs concisely; they return an error code (or do nothing) if `dlsym` resolution fails:

```c
// ndk/media/NdkImageReader.cpp — only compiled for API < 21
#if (__ANDROID_API__ + 0) < 21
#include <media/NdkImageReader.h>
#include "NdkCompatAPI.h"

namespace {
void* resolve(const char* name) {
    if (auto so = NDKMEDIA_NS::mediandk_so()) return dlsym(so, name);
    return nullptr;
}
}

NDKCOMPAT_DEFINE_RET(media_status_t, AImageReader_new, AMEDIA_ERROR_UNSUPPORTED,
    JMI_ARG5(int32_t, int32_t, int32_t, int32_t, AImageReader**))
// ... more stubs
#endif
```

The general dlsym pattern for Case 1:

- `dlopen` is called only once per library (static local variable).
- `__func__` is used as the symbol name to avoid typos and reduce maintenance.
- `decltype(&FunctionName)` provides a type-safe cast of the `void*` returned by `dlsym`.

### NdkCompatAPI.h — Generating dlsym Wrappers

`ndk/NdkCompatAPI.h` provides two macros that generate complete dlsym-based wrapper functions (used for Case 2 above — no JMI fallback):

```c
// For functions with a return value
NDKCOMPAT_DEFINE_RET(return_type, function_name, failure_return_value, JMI_ARGn(...))

// For void functions
NDKCOMPAT_DEFINE_VOID(function_name, JMI_ARGn(...))
```

Each expansion produces an `extern "C"` function that resolves the symbol via a `resolve()` helper (provided by the including file) and calls it, or returns `failure_return_value` if resolution fails.

The `JMI_ARGn(T1, T2, ...)` macros (from JMI) expand to a triple `(type-list), (typed-param-list), (param-list)` used to fill in the function signature and the forwarding call site.

Example:

```c
NDKCOMPAT_DEFINE_RET(aaudio_result_t, AAudio_createStreamBuilder,
    AAUDIO_ERROR_UNIMPLEMENTED, JMI_ARG1(AAudioStreamBuilder**))
```

expands to:

```c
extern "C" AAUDIO_API aaudio_result_t AAudio_createStreamBuilder(AAudioStreamBuilder** p1) {
    static const auto fp = reinterpret_cast<decltype(&AAudio_createStreamBuilder)>(resolve("AAudio_createStreamBuilder"));
    if (fp)
        return fp(p1);
    return AAUDIO_ERROR_UNIMPLEMENTED;
}
```

### API Names and Parameters

All NDK API names follow the Android NDK convention:

- Prefix: the initial `A` (Android) followed by the subsystem name: `AMediaCodec_*`, `AImage_*`, `AImageReader_*`, `AAudioStream_*`, `AAudioStreamBuilder_*`, etc.
- Return type: `media_status_t` (or `aaudio_result_t`) for operations that can fail; concrete value types for pure getters.
- Parameter order: the object pointer (usually `const T*` for read-only, `T*` for mutating) is always first, followed by input parameters, with output parameters (pointers) last.

Examples:

```c
// Getter: const object first, output via pointer last
media_status_t AImage_getWidth(const AImage* image, int32_t* width);

// Action: mutable object first, inputs follow
media_status_t AMediaCodec_start(AMediaCodec* codec);

// Multi-output: all outputs at the end
media_status_t AImageReader_acquireNextImage(AImageReader* reader, AImage** image);
```

#### MIT License
>Copyright (c) 2016-2026 WangBin
