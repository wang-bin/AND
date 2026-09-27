#!/usr/bin/env bash
set -euo pipefail
root=$(cd "$(dirname "$0")/../.." && pwd)
: "${JAVA_HOME:?Set JAVA_HOME to a JDK with JNI headers}"
build=$(mktemp -d)
trap 'rm -rf "$build"' EXIT
case "$(uname -s)" in
  Darwin) platform=darwin; library=libCodecCapabilitiesTest.dylib; link=-dynamiclib ;;
  Linux) platform=linux; library=libCodecCapabilitiesTest.so; link=-shared ;;
  *) echo 'Requires macOS or Linux' >&2; exit 1 ;;
esac
read -r -a cxx_flags <<< "${CXXFLAGS:-}"
"${CXX:-clang++}" ${cxx_flags[@]+"${cxx_flags[@]}"} -std=c++23 -O1 -g -fPIC "$link" -pthread \
  -Wno-unguarded-availability -Wno-unsupported-availability-guard \
  -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/$platform" \
  -I"$root/tests/codec-capabilities/stubs" -I"$root" -I"$root/classes" \
  "$root/tests/codec-capabilities/probe.cpp" \
  "$root/ndk/media/NdkMediaCodecInfo.cpp" \
  "$root/classes/android.media.MediaCodecInfo.cpp" \
  "$root/classes/android.util.Range.cpp" \
  "$root/classes/java.lang.Double.cpp" \
  "$root/classes/java.lang.Integer.cpp" \
  "$root/jmi/jmi.cpp" -o "$build/$library"
"$JAVA_HOME/bin/javac" -d "$build" \
  "$root/tests/codec-capabilities/java/android/media/MediaCodecInfo.java" \
  "$root/tests/codec-capabilities/java/CodecCapabilitiesTest.java"
cd "$build"
"$JAVA_HOME/bin/java" -Xcheck:jni -Djava.library.path="$build" -cp "$build" CodecCapabilitiesTest
