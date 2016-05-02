// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <Windows.h>

#include "util/scoped_handle.h"

namespace base {
	namespace win {

		// Like ScopedHandle but for HDC.  Only use this on HDCs returned from
		// GetDC.
		class ScopedGetDC {
		public:
			explicit ScopedGetDC(HWND hwnd)
				: hwnd_(hwnd),
				hdc_(GetDC(hwnd)) {
			}

			~ScopedGetDC() {
				if (hdc_)
					ReleaseDC(hwnd_, hdc_);
			}

			operator HDC() { return hdc_; }

		private:
			HWND hwnd_;
			HDC hdc_;
		};

		// Like ScopedHandle but for HDC.  Only use this on HDCs returned from
		// CreateCompatibleDC, CreateDC and CreateIC.
		class CreateDCTraits {
		public:
			typedef HDC Handle;

			static bool CloseHandle(HDC handle) {
				return ::DeleteDC(handle) != FALSE;
			}

			static bool IsHandleValid(HDC handle) {
				return handle != NULL;
			}

			static HDC NullHandle() {
				return NULL;
			}
			CreateDCTraits() = delete;
			CreateDCTraits(const CreateDCTraits&) = delete;
		};

		typedef GenericScopedHandle<CreateDCTraits> ScopedCreateDC;

	}  // namespace win
}  // namespace base
