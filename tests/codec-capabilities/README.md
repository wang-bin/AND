# Concurrent Java codec capabilities regression

Run with a JDK (JNI headers included) and Clang on macOS or Linux:

```sh
JAVA_HOME=/path/to/jdk tests/codec-capabilities/run.sh
```

The JDK and compiler must target the same host architecture. On Apple Silicon
with an x86_64 JDK, use `CXXFLAGS='-arch x86_64'`. `CXX` selects the compiler.
The runner compiles the actual `NdkMediaCodecInfo.cpp` and JMI implementation;
only `mediandk_so()` / unused format conversion helpers and Android Java classes
are host fixtures. JNI calls run in a real JVM with `-Xcheck:jni`.

Eight native threads probe one shared codec, for 2,000 iterations each. Both
cold first access and retaining a capabilities pointer across subsequent probes
are covered. Each iteration checks supported and unsupported sizes; a Java
exception is injected once per thread to check the `-1` error result and recovery.
Null argument behavior is also checked. The Java fixture returns the same
VideoCapabilities object, as the Android API does; each JMI wrapping operation
still creates a new global handle.

Without synchronization, concurrent probes replace/delete JNI handles while
another thread uses them, producing `Bad global or local ref passed to JNI` or
`Wrong object class or methodID passed to JNI call`. A fixed run must print
`shared codec capabilities: PASS`. Intentional negative-width exceptions may be
printed by JMI. A fatal checked-JNI error is a failure; some JVMs may hang while
multiple threads report fatal errors, so CI should give the process a timeout.

This test allocates no platform decoder. It covers Java reference ownership and
concurrent access, not vendor codec behavior, actual Android playback, or the
API 37+ system NDK implementation. An Android NDK build and device playback test
are still required before shipping a rebuilt SDK.
