#pragma once

#include <windows.h>
#include <memory>

namespace gui {
	class Board;

	class Window {
	public:
		static bool Register(HINSTANCE);
		static void CleanUp(HINSTANCE);
		Window(HINSTANCE, int);
		~Window();

		Window(const Window&) = delete;
		const Window& operator=(const Window&) = delete;

		bool Initialize();

		HWND hwnd() const { return hwnd_; }
		HINSTANCE hinstance() const { return reinterpret_cast<HINSTANCE>(GetWindowLongPtr(hwnd_, GWL_HINSTANCE)); }
	private:
		void CloseWindow();

		std::unique_ptr<Board> board;
		HWND hwnd_;
	};
}