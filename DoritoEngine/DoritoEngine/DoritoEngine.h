#pragma once
#include "InputManager.h"
#include "SceneManager.h"
#include "SFML/Graphics.hpp"

struct GameInfo
{
	struct WindowSettings
	{
		unsigned int width = 0;
		unsigned int height = 0;
		std::string title = "";
		bool isVsyncOn = true;
		unsigned int frameCap = 60;

	}
	windowSettings = WindowSettings();

	InputManager* pInput = nullptr;
	SceneManager* pSceneManager = nullptr;
};

class DoritoEngine
{
public:
	DoritoEngine();
	~DoritoEngine() = default;

	void Initialize(unsigned int width, unsigned int height, const std::string& title, bool vSyncOn = true, unsigned int frameCap = 0);
	void Run();
	void Cleanup();

	const GameInfo& GetGameInfo() { return m_GameInfo; };

private:
	sf::Clock m_Clock;
	GameInfo m_GameInfo;

	const float dt = 1.f / 60.f;
};

