#include "DoritoPCH.h"
#include "DoritoEngine.h"

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

void DoritoEngine::Initialize(unsigned int width, unsigned int height, const std::string& title)
{
	m_GameInfo.windowSettings.width = width;
	m_GameInfo.windowSettings.height = height;
	m_GameInfo.windowSettings.title = title;
	m_GameInfo.windowSettings.isVsyncOn = true;

	m_GameInfo.pInput->Initialize();

	Renderer::GetInstance()->Init(m_GameInfo.windowSettings);

	Renderer::GetInstance()->SetDebugRendering(false);
}

void DoritoEngine::Run()
{
	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance()->Init("../Resources/");

#ifdef TEST_GAME
	auto game = Game();
	game.LoadGame(m_GameInfo);
#endif 

	sf::Clock clock;

	auto renderer = Renderer::GetInstance();

	//float newTime, frameTime;
	//float currentTime = m_Clock.getElapsedTime().asSeconds();
	//float accumulator = 0.f;

	while (renderer->GetRenderer().isOpen())
	{
		//newTime = m_Clock.getElapsedTime().asSeconds();
		//frameTime = newTime - currentTime;
		//frameTime = std::min(frameTime, 0.25f);
		//currentTime = newTime;

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
