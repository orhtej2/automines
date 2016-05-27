#include "gui/window.h"

#include <stdexcept>

#include "gui/board.h"

namespace {
	gui::Window* getWindow(HWND hwnd) {
		return reinterpret_cast<gui::Window*>(GetWindowLongPtr(hwnd, 0));
	}
	const char g_szClassName[] = "minesweeper";

	// Step 4: the Window Procedure
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		return 0;
	}
}

namespace gui {
	bool Window::Register(HINSTANCE hInstance)
	{
		WNDCLASSEX wc;
		//Step 1: Registering the Window Class
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = 0;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;// );
		wc.cbWndExtra = sizeof(Window*);
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = g_szClassName;
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&wc))
		{
			MessageBox(NULL, "Window Registration Failed!", "Error!",
				MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		return true;
	}

	void Window::CleanUp(HINSTANCE hInstance) {
	}

	Window::Window(HINSTANCE hInstance, int nCmdShow) {
		hwnd_ = CreateWindowEx(
			WS_EX_CLIENTEDGE | WS_EX_COMPOSITED | WS_EX_CONTROLPARENT | WS_EX_NOINHERITLAYOUT,
			g_szClassName,
			"Minesweeper",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
			NULL, NULL, hInstance, this);

		if (hwnd_ == NULL)
		{
			MessageBox(NULL, "Window Creation Failed!", "Error!",
				MB_ICONEXCLAMATION | MB_OK);

			throw std::exception();
		}

		SetWindowLongPtr(hwnd_, 0, reinterpret_cast<LONG_PTR>(this));
		Initialize();

		ShowWindow(hwnd_, nCmdShow);
		UpdateWindow(hwnd_);
	}

	bool Window::Initialize() {
		const RECT rect = { 10, 10, 200, 200 };
		board.reset(new Board(hwnd_, rect));
		return true;
	}

	void Window::CloseWindow() {
		if (hwnd_ != NULL) {
			::CloseWindow(hwnd_);
		}

		hwnd_ = NULL;
	}

	Window::~Window() {
			Window::CloseWindow();
	}
}