#include "Game.h"
#include "MiniginPCH.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"

using namespace std;
using namespace std::chrono;

#define TEST_SCENE

#ifdef TEST_SCENE
#include "TestScene.h"
#endif // TEST_SCENE

void Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1024,
		768,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

void Game::LoadGame() const
{
#ifdef TEST_SCENE
	SceneManager::GetInstance().CreateScene(new TestScene("Test"));
#endif
}

void Game::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Game::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	bool doContinue = true;
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.f;
	auto msPerUpdate = duration_cast<duration<float>>(milliseconds(MsPerFrame));

	while (doContinue)
	{
		const auto currentTime = high_resolution_clock::now();
		float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		lag += deltaTime;

		doContinue = input.ProcessInput();

		while (lag >= msPerUpdate.count())
		{
			sceneManager.Update(msPerUpdate.count());
			lag -= msPerUpdate.count();
		}
		renderer.Render();

		auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
		this_thread::sleep_for(sleepTime);
	}

	Cleanup();
}
