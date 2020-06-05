#include "Game.h"
#include "MiniginPCH.h"

#include <chrono>
#include <thread>

#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"


#define TEST_SCENE

#ifdef TEST_SCENE
#include "TestScene.h"
#include "TestScene2.h"
#endif

void Game::Initialize(unsigned int width, unsigned int height, const std::string& title)
{
	m_GameInfo = std::make_shared<GameInfo>();

	m_GameInfo->window.create(VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close);
	
	m_GameInfo->input = InputManager::GetInstance();
	m_GameInfo->sceneManager = SceneManager::GetInstance();


	//Renderer::GetInstance().Init(m_Window);
}

void Game::LoadGame() const
{
#ifdef TEST_SCENE
	m_GameInfo->sceneManager.CreateScene(new TestScene("Test"));
	m_GameInfo->sceneManager.CreateScene(new TestScene2("Test2"));
	m_GameInfo->sceneManager.SetActiveGameScene("Test2");
#endif
}

void Game::Cleanup()
{
	//Renderer::GetInstance().Destroy();
	//SDL_DestroyWindow(m_Window);
	//m_Window = nullptr;
	//SDL_Quit();


}

void Game::Run()
{
	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	auto& renderer = Renderer::GetInstance();

	float newTime, frameTime;

	float currentTime = m_Clock.getElapsedTime().asSeconds();
	float accumulator = 0.f;

	while (m_GameInfo->window.isOpen())
	{
		newTime = m_Clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;
		m_GameInfo->input.ProcessInput();
		
		while (accumulator >= dt)
		{
			m_GameInfo->sceneManager.Update(dt);

			accumulator -= dt;
		}

		renderer.Render();
	}
}
