#pragma once

#include <string>

#include "Game.h"
#include "GamePresenter.h"

class GameData {
public:
	GameData(const std::string& name) : paint(game), name(name) {}
	const Game& get_game() const { return game; }
	Game& get_game() { return game; }
	const GamePresenter& get_game_presenter() const { return paint; }
	GamePresenter& get_game_presenter() { return paint; }

private:
	Game game;
	GamePresenter paint;
	const std::string name;
};