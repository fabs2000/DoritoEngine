#include "DoritoPCH.h"
#include "Game.h"

#include "Scene.h"

#define TEST_SCENE

#ifdef TEST_SCENE
#include "TestScene.h"
#include "TestScene2.h"
#endif

void Game::LoadGame(const GameInfo& gameInfo)
{
#ifdef TEST_SCENE
	gameInfo.pSceneManager->CreateScene(new TestScene("Test", gameInfo));
	gameInfo.pSceneManager->CreateScene(new TestScene2("Test2", gameInfo));
	gameInfo.pSceneManager->SetActiveGameScene("Test");
#endif
}
