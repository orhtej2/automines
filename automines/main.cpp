#include <windows.h>

#include "Game.h"

#include "gui/window.h"
#include "gui/board.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	gui::Window::Register(hInstance);
	gui::Board::Register(hInstance);

	Game game;
	gui::Window window(hInstance, nCmdShow);

	MSG Msg;
	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	gui::Window::CleanUp(hInstance);
	gui::Board::CleanUp(hInstance);

	return Msg.wParam;
}