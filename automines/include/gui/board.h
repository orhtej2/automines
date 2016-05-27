#pragma once

#include <windows.h>

#include "gui/window.h"
#include "logic/Game.h"
#include "util/scoped_gdiobject.h"

namespace gui {
	class Board {
	public:
		static bool Register(HINSTANCE hInstance);
		static bool CleanUp(HINSTANCE hInstance);
		Board(const Board&) = delete;
		virtual ~Board() = default;
		const Board& operator=(const Board&) = delete;

		void Paint(HDC hdc);
		Board(HWND parent, const RECT& bounds);
	protected:

		virtual void DrawBorder(HDC hdc, const RECT& bounds) {}
		virtual void DrawBackground(HDC hdc, const RECT& bounds) {}
		virtual void DrawDrawField(HDC hdc, const RECT& bounds) {}

		virtual void DrawTile(HDC hdc, const RECT& bounds, logic::Game::PlayingField::Tiles tile) {}
	private:
		static bool s_registered;

		HWND hwnd_;
	};
}