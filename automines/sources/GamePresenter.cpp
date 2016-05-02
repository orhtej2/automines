#include <Windows.h>

#include "util/scoped_hdc.h"
#include "util/scoped_gdiobject.h"

#include "GamePresenter.h"
#include "GameData.h"

#define PTR_SIZE sizeof(GameData*)
#define LENGTH ((PTR_SIZE + 1)/sizeof(LONG_PTR))
#define SIZE_IN_BYTES (sizeof(LONG_PTR)*LENGTH)

void SetGame(HWND hwnd) {
	SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(new GameData("minesweeper")));
}

void ReleaseGame(HWND hwnd) {
}

void PaintWindow(HWND hwnd) {
	HWND parent = GetParent(hwnd);
	GameData* game_data = reinterpret_cast<GameData*>(GetWindowLongPtr(parent, GWLP_USERDATA));
	game_data->get_game_presenter().paint(hwnd);
}

void GamePresenter::paint(HWND hwnd) const {
	base::win::ScopedGetDC hdc(hwnd);
	RECT r;
	GetClientRect(hwnd, &r);
	SetTextColor(hdc, 0x124512);
	PatBlt(hdc, r.left, r.top, r.right - r.left, r.bottom - r.top, BLACKNESS);
	DrawText(hdc, TEXT("LONGLONG text"), -1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}