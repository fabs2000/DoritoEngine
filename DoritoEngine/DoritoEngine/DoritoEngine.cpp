#include "DoritoPCH.h"
#include "DoritoEngine.h"

#include "../Digger/Game.h"

#include "SFML/System/Clock.hpp"

#include "Renderer.h"
#include "ResourceManager.h"

#define TEST_GAME

DoritoEngine::DoritoEngine()
	: m_GameInfo()
{
	m_GameInfo.pInput = InputManager::GetInstance();
	m_GameInfo.pSceneManager = SceneManager::GetInstance();
}


// frameCap = 0 for uncapped frame rate
void DoritoEngine::Initialize(unsigned int width, unsigned int height, const std::string& title, bool vSyncOn, unsigned int frameCap)
{
	m_GameInfo.windowSettings.width = width;
	m_GameInfo.windowSettings.height = height;
	m_GameInfo.windowSettings.title = title;
	m_GameInfo.windowSettings.isVsyncOn = vSyncOn;
	m_GameInfo.windowSettings.frameCap = frameCap;

	m_GameInfo.pInput->Initialize();

	Renderer::GetInstance()->Init(m_GameInfo.windowSettings);

	Renderer::GetInstance()->SetDebugRendering(false);
}

void DoritoEngine::Run()
{
	// Tell the resource manager where he can find the game data
	ResourceManager::GetInstance()->Init("../Resources/");

#ifdef TEST_GAME
	auto game = Game();
	game.LoadGame(m_GameInfo);
#endif 

	sf::Clock clock;

	auto renderer = Renderer::GetInstance();

	while (renderer->GetRenderer().isOpen())
	{
		m_GameInfo.pInput->ProcessInput(renderer->GetRenderer());
		
		sf::Time time = clock.getElapsedTime();

		m_GameInfo.pSceneManager->Update(time.asSeconds());
		
		clock.restart().asSeconds();
		renderer->Render();
	}
}

void DoritoEngine::Cleanup()
{
	ResourceManager::GetInstance()->Destroy();
	m_GameInfo.pSceneManager->Destroy();
}
