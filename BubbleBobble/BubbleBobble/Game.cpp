#include "DoritoPCH.h"
#include "Game.h"

#include "Scene.h"

#define TEST_SCENE

#ifdef TEST_SCENE
#include "MainLevel.h"
#include "Menu.h"
#endif

void Game::LoadGame(const GameInfo& gameInfo)
{
#ifdef TEST_SCENE
	gameInfo.pSceneManager->CreateScene(new MainLevel("Main", gameInfo));
	gameInfo.pSceneManager->CreateScene(new MenuScene("Menu", gameInfo));
	gameInfo.pSceneManager->SetActiveGameScene("Menu");
#endif
}
