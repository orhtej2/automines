#include "gui/board.h"

namespace {
	const char g_szBoardClassName[] = "minesweeper_board_control";

	gui::Board* getBoard(HWND hwnd) {
		return reinterpret_cast<gui::Board*>(GetWindowLongPtr(hwnd, 0));
	}

	static LRESULT CALLBACK
		ControlWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg) {
		case WM_PAINT:
		{
			PAINTSTRUCT paint;
			HDC hDC = BeginPaint(hwnd, &paint);
			gui::Board* board = getBoard(hwnd);
			board->Paint(hDC);
			EndPaint(hwnd, &paint);
			break;
		}
		return 0;
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

namespace gui {
	bool Board::s_registered = false;
	
	bool Board::Register(HINSTANCE hInstance) {
		if (s_registered)
			return true;

		WNDCLASSEX wc;
		//Step 1: Registering the Window Class
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = ControlWndProc;
		wc.cbClsExtra = 0;// sizeof(GameData*);
		wc.cbWndExtra = sizeof(Board*);
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = g_szBoardClassName;
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&wc))
		{
			return false;
		}

		s_registered = true;
		return true;
	}

	bool Board::CleanUp(HINSTANCE hInstance) {
		if (!s_registered)
			return true;
		s_registered = false;
		return UnregisterClass(g_szBoardClassName, hInstance) != FALSE;
	}

	Board::Board(HWND parent, const RECT& bounds) {
		hwnd_ = CreateWindowEx(WS_EX_NOPARENTNOTIFY, 
			g_szBoardClassName, nullptr, 
			WS_CHILD | WS_VISIBLE, bounds.left, bounds.top, bounds.right, bounds.bottom, parent, nullptr, 
			reinterpret_cast<HINSTANCE>(GetWindowLongPtr(parent, GWLP_HINSTANCE)), nullptr);
		SetWindowLongPtr(hwnd_, 0, reinterpret_cast<LONG_PTR>(this));
	}

	void Board::Paint(HDC hDC) {
		RECT rect;
		GetClientRect(hwnd_, &rect);
		DrawBackground(hDC, rect);
		DrawBorder(hDC, rect);

		//RECT rect;
		//GetClientRect(hwnd_, &rect);
		//SelectObject(hDC, pen);
		//MoveToEx(hDC, rect.left, rect.top, 0);
		//LineTo(hDC, rect.right, rect.top);
		//LineTo(hDC, rect.right, rect.bottom);
		//LineTo(hDC, rect.left, rect.bottom);
		//LineTo(hDC, rect.left, rect.top);
	}
}