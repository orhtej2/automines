// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <Windows.h>

namespace base {
	namespace win {

		// Like ScopedHandle but for GDI objects.
		template<class T>
		class ScopedGDIObject {
		public:
			ScopedGDIObject() : object_(NULL) {}
			ScopedGDIObject(const ScopedGDIObject&) = delete;
			const ScopedGDIObject& operator=(const ScopedGDIObject&) = delete;
			explicit ScopedGDIObject(T object) : object_(object) {}

			~ScopedGDIObject() {
				Close();
			}

			T Get() {
				return object_;
			}

			void Set(T object) {
				if (object_ && object != object_)
					Close();
				object_ = object;
			}

			ScopedGDIObject& operator=(T object) {
				Set(object);
				return *this;
			}

			T release() {
				T object = object_;
				object_ = NULL;
				return object;
			}

			operator T() { return object_; }

		private:
			void Close() {
				if (object_)
					DeleteObject(object_);
			}

			T object_;
		};

		// An explicit specialization for HICON because we have to call DestroyIcon()
		// instead of DeleteObject() for HICON.
		template<>
		void inline ScopedGDIObject<HICON>::Close() {
			if (object_)
				DestroyIcon(object_);
		}

		// Typedefs for some common use cases.
		typedef ScopedGDIObject<HBITMAP> ScopedBitmap;
		typedef ScopedGDIObject<HRGN> ScopedRegion;
		typedef ScopedGDIObject<HFONT> ScopedHFONT;
		typedef ScopedGDIObject<HICON> ScopedHICON;
		typedef ScopedGDIObject<HBRUSH> ScopedBrush;
		typedef ScopedGDIObject<HPEN> ScopedPen;

	}  // namespace win
}  // namespace base
