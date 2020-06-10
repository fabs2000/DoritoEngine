#pragma once
#include "DoritoEngine.h"
#include "SFML/Graphics.hpp"

class Game
{
public:
	Game() = default;
	~Game() = default;

	void LoadGame(const GameInfo& gameInfo);
};

