/*
 * AND: Android Native Dev in Modern C++ based on JMI
 * Copyright (C) 2026 Wang Bin - wbsecg1@gmail.com
 * https://github.com/wang-bin/AND
 * https://github.com/wang-bin/JMI
 * MIT License
 */

#include "surface_texture_p.hpp"
#include "surface_texture.hpp"
#include "../../classes/android.graphics.SurfaceTexture.hpp"
#include "jmi/jmi.h"

#include <android/native_window_jni.h>
#include <android/surface_texture.h>

#pragma comment(lib, "libandroid.so")

#include <cerrno>
#include <iostream>
#include <utility>

using namespace jmi;

namespace ndk {
namespace android {

struct SurfaceTag : jmi::ClassTag { static constexpr auto name() { return JMISTR("android/view/Surface"); } };
using Surface = jmi::JObject<SurfaceTag>;

ASurfaceTexture* fromJmi(jmi::android::graphics::SurfaceTexture&& obj)
{
	return new ASurfaceTexture{nullptr, new jmi::android::graphics::SurfaceTexture(std::move(obj))};
}

ASurfaceTexture* fromNdk(::ASurfaceTexture* obj)
{
	if (!obj)
		return nullptr;
	return new ASurfaceTexture{obj, nullptr};
}

::ASurfaceTexture* toNdk(const ASurfaceTexture* obj)
{
	if (!obj)
		return nullptr;
	return obj->ndk_;
}

void ASurfaceTexture_release(ASurfaceTexture* st)
{
	if (!st)
		return;
	if (isASurfaceTextureNdk()) {
		if (__builtin_available(android 28, *))
			::ASurfaceTexture_release(toNdk(st));
	}
	delete st->jni_;
	delete st;
}

ANativeWindow* ASurfaceTexture_acquireANativeWindow(ASurfaceTexture* st)
{
	if (isASurfaceTextureNdk()) {
		if (__builtin_available(android 28, *))
			return ::ASurfaceTexture_acquireANativeWindow(toNdk(st));
	}

	if (!st || !st->jni_)
		return nullptr;

	Surface surface;
	if (!surface.create(*st->jni_)) {
		std::clog << __PRETTY_FUNCTION__ << " ERROR: " << surface.error() << std::endl;
		return nullptr;
	}

	return ANativeWindow_fromSurface(getEnv(), surface.id());
}

int ASurfaceTexture_attachToGLContext(ASurfaceTexture* st, uint32_t texName)
{
	if (isASurfaceTextureNdk()) {
		if (__builtin_available(android 28, *))
			return ::ASurfaceTexture_attachToGLContext(toNdk(st), texName);
	}

	if (!st || !st->jni_)
		return -EINVAL;

	st->jni_->attachToGLContext(static_cast<jint>(texName));
	if (st->jni_->error().empty())
		return 0;
	std::clog << __PRETTY_FUNCTION__ << " ERROR: " << st->jni_->error() << std::endl;
	return -EINVAL;
}

int ASurfaceTexture_detachFromGLContext(ASurfaceTexture* st)
{
	if (isASurfaceTextureNdk()) {
		if (__builtin_available(android 28, *))
			return ::ASurfaceTexture_detachFromGLContext(toNdk(st));
	}

	if (!st || !st->jni_)
		return -EINVAL;

	st->jni_->detachFromGLContext();
	if (st->jni_->error().empty())
		return 0;
	std::clog << __PRETTY_FUNCTION__ << " ERROR: " << st->jni_->error() << std::endl;
	return -EINVAL;
}

int ASurfaceTexture_updateTexImage(ASurfaceTexture* st)
{
	if (isASurfaceTextureNdk()) {
		if (__builtin_available(android 28, *))
			return ::ASurfaceTexture_updateTexImage(toNdk(st));
	}

	if (!st || !st->jni_)
		return -EINVAL;

	st->jni_->updateTexImage();
	if (st->jni_->error().empty())
		return 0;
	std::clog << __PRETTY_FUNCTION__ << " ERROR: " << st->jni_->error() << std::endl;
	return -EINVAL;
}

void ASurfaceTexture_getTransformMatrix(ASurfaceTexture* st, float mtx[16])
{
	if (isASurfaceTextureNdk()) {
		if (__builtin_available(android 28, *)) {
			::ASurfaceTexture_getTransformMatrix(toNdk(st), mtx);
			return;
		}
	}

	if (!st || !st->jni_ || !mtx)
		return;

	auto& m = *reinterpret_cast<jfloat(*)[16]>(mtx);
	st->jni_->getTransformMatrix(std::ref(m));
	if (!st->jni_->error().empty())
		std::clog << __PRETTY_FUNCTION__ << " ERROR: " << st->jni_->error() << std::endl;
}

int64_t ASurfaceTexture_getTimestamp(ASurfaceTexture* st)
{
	if (isASurfaceTextureNdk()) {
		if (__builtin_available(android 28, *))
			return ::ASurfaceTexture_getTimestamp(toNdk(st));
	}

	if (!st || !st->jni_)
		return -1;

	const auto ts = static_cast<int64_t>(st->jni_->getTimestamp());
	if (st->jni_->error().empty())
		return ts;
	std::clog << __PRETTY_FUNCTION__ << " ERROR: " << st->jni_->error() << std::endl;
	return -1;
}

} // namespace android
} // namespace ndk
