project(AND)
cmake_minimum_required(VERSION 3.0)
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17) # TODO: option
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(POLICY CMP0063) # visibility. since 3.3
  cmake_policy(SET CMP0063 NEW)
endif()
set(CMAKE_CXX_VISIBILITY_PRESET hidden) #use with -fdata-sections -ffunction-sections to reduce target size
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

file(GLOB CLASSES_SRC classes/*.cpp)
file(GLOB NDK_SRC ndk/media/*.cpp)

add_library(AND jmi/jmi.cpp ${CLASSES_SRC} ${NDK_SRC})
target_link_libraries(AND PUBLIC jmi)
target_include_directories(AND PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/classes)

