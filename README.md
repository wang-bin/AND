# Android Native Dev in Modern C++

## Directories:

- classes: C++ classes for java implemented in [JMI](https://github.com/wang-bin/JMI)
- ndk/media: libmediandk APIs(requires api level 21+) implemented for all api levels. Either use libmediandk C api directly or use JMI classes, controlled by user at runtime
- ndk/aaudio: compatibile with target < 26 without code change

## NDK Directory Design

### CMake Targets

The `ndk/` subdirectory provides two CMake targets, both declared as `OBJECT` libraries (not `STATIC`):

- **`mediandk`**: Implements `libmediandk` APIs. When the target Android API level is ≥ 21, the build links against `libmediandk.so` (`-lmediandk`) and relies on weak symbols for any APIs not present in that API level. When targeting API < 21, the extra source files `NdkImage.cpp` and `NdkImageReader.cpp` are added, providing pure-dlsym stubs for those APIs.
- **`aaudio`**: Implements `libaaudio` APIs. Only built when the target Android API level is < 26 (otherwise `libaaudio.so` is linked directly by the consuming project). Always links against `dl` for `dlsym`.

**Why `OBJECT` instead of `STATIC`?** Weak symbols must remain unresolved until the final link step so that the linker can resolve them against the real symbols from platform libraries (e.g. `AImageReader` APIs from `libmediandk.so` on API 26+). A `STATIC` library would cause these weak symbols to be "locked in" at archive creation time, preventing correct resolution. Using `OBJECT` libraries preserves the object files individually so the final link sees all symbols together.

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

Use a plain `__attribute__((weak))` declaration (without a dlsym fallback) when:

- The shared library is already linked (`-lmediandk`, `-laaudio`, etc.), so the symbol *will* be resolved by the linker from that library if the API level supports it.
- You need a graceful no-op or null result on older devices where the symbol does not exist in the linked library, rather than a hard linker error.
- The same object file may be linked into multiple modules; `weak` prevents duplicate-symbol errors in that case.

Example from `ndk/media/NdkMediaCodec.cpp`:

```c
// null if not present in the linked libandroid.so (pre-API 26 devices)
extern "C" jobject ANativeWindow_toSurface(JNIEnv* env, ANativeWindow* window) __attribute__((weak));
```

At runtime, check whether the pointer is non-null before calling it, or use `__builtin_available` when NDK ≥ 23 and `__ANDROID_UNAVAILABLE_SYMBOLS_ARE_WEAK__` is defined.

### When to Use dlsym

Use `dlsym` for runtime resolution when:

- The shared library (`libmediandk.so`, `libaaudio.so`, `libandroid.so`) is **not** linked at build time (e.g. targeting API < 21 for mediandk, or API < 26 for aaudio).
- The API may or may not exist on the running device and you need a graceful fallback (JNI path or returning an error code).
- You want to avoid hard link-time dependencies on optional platform libraries.

The general dlsym pattern used throughout this codebase:

```c
// Lazy-load the shared library once
void* mediandk_so() {
    static void* dso = dlopen("libmediandk.so", RTLD_LAZY | RTLD_LOCAL);
    return dso;
}

// Resolve and call the symbol; fall back to JNI if unavailable
AMediaCodec* AMediaCodec_createCodecByName(const char* name) {
    auto so = mediandk_so();
    if (so) {
        static const auto fp = (decltype(&AMediaCodec_createCodecByName))dlsym(so, __func__);
        return fromNdk(fp(name));  // fromNdk: wraps the NDK AMediaCodec* in the local AMediaCodec struct
    }
    // JNI fallback
    auto obj = android::media::MediaCodec::createByCodecName(name);
    ...
}
```

Key points:
- `dlopen` is called only once per library (static local variable).
- `__func__` is used as the symbol name to avoid typos and reduce maintenance.
- `decltype(&FunctionName)` provides a type-safe cast of the `void*` returned by `dlsym`.

### NdkCompatAPI.h — Generating dlsym Wrappers

`ndk/NdkCompatAPI.h` provides two macros that generate complete dlsym-based wrapper functions:

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
