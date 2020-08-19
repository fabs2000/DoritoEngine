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

	auto renderer = Renderer::GetInstance();

	auto prevTime = std::chrono::high_resolution_clock::now();

	while (renderer->GetRenderer().isOpen())
	{
		auto currTime = std::chrono::high_resolution_clock::now();
		float dt = std::min(std::chrono::duration<float>(currTime - prevTime).count(), 0.1f);
		prevTime = currTime;

		m_GameInfo.pInput->ProcessInput(renderer->GetRenderer());
		
		m_GameInfo.pSceneManager->Update(dt);

		renderer->Render();
	}
}

void DoritoEngine::Cleanup()
{
	ResourceManager::GetInstance()->Destroy();
	m_GameInfo.pSceneManager->Destroy();
}
