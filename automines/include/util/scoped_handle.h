// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <Windows.h>

namespace base {
	namespace win {

		// Generic wrapper for raw handles that takes care of closing handles
		// automatically. The class interface follows the style of
		// the ScopedFILE class with two additions:
		//   - IsValid() method can tolerate multiple invalid handle values such as NULL
		//     and INVALID_HANDLE_VALUE (-1) for Win32 handles.
		//   - Set() (and the constructors and assignment operators that call it)
		//     preserve the Windows LastError code. This ensures that GetLastError() can
		//     be called after stashing a handle in a GenericScopedHandle object. Doing
		//     this explicitly is necessary because of bug 528394 and VC++ 2015.
		template <class Traits>
		class GenericScopedHandle {

		public:
			typedef typename Traits::Handle Handle;

			GenericScopedHandle() : handle_(Traits::NullHandle()) {}

			explicit GenericScopedHandle(Handle handle) : handle_(Traits::NullHandle()) {
				Set(handle);
			}

			GenericScopedHandle(GenericScopedHandle&& other)
				: handle_(Traits::NullHandle()) {
				Set(other.Take());
			}

			~GenericScopedHandle() {
				Close();
			}

			bool IsValid() const {
				return Traits::IsHandleValid(handle_);
			}

			GenericScopedHandle& operator=(GenericScopedHandle&& other) {
				DCHECK_NE(this, &other);
				Set(other.Take());
				return *this;
			}

			void Set(Handle handle) {
				if (handle_ != handle) {
					// Preserve old LastError to avoid bug 528394.
					auto last_error = ::GetLastError();
					Close();

					if (Traits::IsHandleValid(handle)) {
						handle_ = handle;
						Verifier::StartTracking(handle, this, BASE_WIN_GET_CALLER,
							tracked_objects::GetProgramCounter());
					}
					::SetLastError(last_error);
				}
			}

			Handle Get() const {
				return handle_;
			}

			// Transfers ownership away from this object.
			Handle Take() {
				Handle temp = handle_;
				handle_ = Traits::NullHandle();
				return temp;
			}

			// Explicitly closes the owned handle.
			void Close() {
				if (Traits::IsHandleValid(handle_)) {
					Traits::CloseHandle(handle_);
					handle_ = Traits::NullHandle();
				}
			}

		private:
			Handle handle_;
		};

		// The traits class for Win32 handles that can be closed via CloseHandle() API.
		class HandleTraits {
		public:
			HandleTraits() = delete;
			HandleTraits(const HandleTraits&) = delete;
			typedef HANDLE Handle;

			// Closes the handle.
			static bool CloseHandle(HANDLE handle) {
				return ::CloseHandle(handle) != FALSE;
			}

			// Returns true if the handle value is valid.
			static bool IsHandleValid(HANDLE handle) {
				return handle != NULL && handle != INVALID_HANDLE_VALUE;
			}

			// Returns NULL handle value.
			static HANDLE NullHandle() {
				return NULL;
			}
		};

		typedef GenericScopedHandle<HandleTraits> ScopedHandle;

		// This should be called whenever the OS is closing a handle, if extended
		// verification of improper handle closing is desired. If |handle| is being
		// tracked by the handle verifier and ScopedHandle is not the one closing it,
		// a CHECK is generated.
		void OnHandleBeingClosed(HANDLE handle);

	}  // namespace win
}  // namespace base
