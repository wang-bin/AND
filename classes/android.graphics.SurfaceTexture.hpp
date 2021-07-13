/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2018-2021 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#pragma once
#include "jmi/jmi.h"

namespace jmi {
namespace android {
namespace graphics {

class SurfaceTexture : public jmi::JObject<SurfaceTexture>
{
public:
    class OnFrameAvailableListener : public jmi::JObject<OnFrameAvailableListener> {
    public:
        using Base = jmi::JObject<OnFrameAvailableListener>;
        using Base::Base; // inherits ctors
        static constexpr auto name() { return JMISTR("android/graphics/SurfaceTexture$OnFrameAvailableListener");}
        virtual void onFrameAvailable(SurfaceTexture surfaceTexture) {} // failed to evaluatel signature if pure
    };

    using Base = jmi::JObject<SurfaceTexture>;
    using Base::Base; // inherits ctors
    static constexpr auto name() { return JMISTR("android/graphics/SurfaceTexture");}
    // create: (int texName), (int texName, boolean singleBufferMode), (boolean singleBufferMode)
    void attachToGLContext(jint texName);
    void detachFromGLContext();
    jlong getTimestamp() const;
    void getTransformMatrix(std::reference_wrapper<jfloat[16]> mtx) const;
    jboolean isReleased() const;
    void release();
    void releaseTexImage();
    void setDefaultBufferSize(jint width, jint height);
    void setOnFrameAvailableListener(std::reference_wrapper<const SurfaceTexture::OnFrameAvailableListener> listener);
    //void setOnFrameAvailableListener(SurfaceTexture::OnFrameAvailableListener listener, Handler handler);
    void updateTexImage();
};
} // namespace graphics
} // namespace android
} // namespace jmi