#pragma once

#include <memory>

#include "Game.h"

class Bitmap {
private:
	std::unique_ptr<unsigned char[]> back_buffer;
};

class GamePresenter {
public:
	GamePresenter(const Game& game) : game(game) {}
	void paint(HWND hwnd) const;
private:
	const Game& game;
	Bitmap bitmap;
};

void SetGame(HWND hwnd);
void ReleaseGame(HWND hwnd);
void PaintWindow(HWND hwnd);