project(AND)
cmake_minimum_required(VERSION 3.16)
if(NOT ANDROID)
  return()
endif()
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 23)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(POLICY CMP0063) # visibility. since 3.3
  cmake_policy(SET CMP0063 NEW)
endif()
set(CMAKE_CXX_VISIBILITY_PRESET hidden) #use with -fdata-sections -ffunction-sections to reduce target size
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

if(ANDROID)
  set(_android_api "")
  if(DEFINED ANDROID_PLATFORM_LEVEL)
    set(_android_api ${ANDROID_PLATFORM_LEVEL})
  elseif(DEFINED ANDROID_NATIVE_API_LEVEL)
    set(_android_api ${ANDROID_NATIVE_API_LEVEL})
  elseif(DEFINED ANDROID_PLATFORM)
    string(REGEX REPLACE "android-([0-9]+)" "\\1" _android_api "${ANDROID_PLATFORM}")
  elseif(DEFINED CMAKE_SYSTEM_VERSION)
    string(REGEX MATCH "^[0-9]+" _android_api "${CMAKE_SYSTEM_VERSION}")
  else()
    message(FATAL_ERROR "Cannot determine Android API level")
  endif()
endif()

file(GLOB CLASSES_SRC classes/*.cpp)
file(GLOB NDK_SRC ndk/media/*.cpp)
file(GLOB AAUDIO_SRC ndk/aaudio/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/classes)

add_subdirectory(jmi)
add_library(android_classes STATIC ${CLASSES_SRC})
target_link_libraries(android_classes PUBLIC jmi)
target_include_directories(android_classes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/classes)
# use OBJECT instead of STATIC to ensure weak symbols are resolved in final link, e.g. AImageReader in api 26+
add_library(mediandk OBJECT ${NDK_SRC})
target_include_directories(mediandk INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/ndk)
target_link_libraries(mediandk PUBLIC android_classes)
if(_android_api GREATER_EQUAL 21) # libmediandk exists since api 21
  target_link_libraries(mediandk PRIVATE -lmediandk)
endif()
if(_android_api LESS 26)
# TODO: add AImageReader loader
endif()

if(_android_api LESS 26)
# use OBJECT instead of STATIC to ensure weak symbols are resolved in final link
  add_library(aaudio OBJECT ${AAUDIO_SRC})
  target_link_libraries(aaudio PRIVATE dl)
endif()