#pragma once

#include "InputManager.h"
#include "SceneManager.h"
#include "SFML/Graphics.hpp"
#include "SFML/System/Clock.hpp"

struct GameInfo
{
	sf::RenderWindow window;
	InputManager input;
	SceneManager sceneManager;
};

class Game
{
public:
	void Initialize(unsigned int width, unsigned int height, const std::string& title);
	void Run();
	void Cleanup();

	GameInfo& GetGameInfo() { return *m_GameInfo; };

private:
	void LoadGame() const;

	sf::Clock m_Clock;
	std::shared_ptr<GameInfo> m_GameInfo;

	const float dt = 1.f / 60.f;
};

