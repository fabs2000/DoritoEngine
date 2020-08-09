#include "DoritoPCH.h"
#include "Game.h"

#include "Scene.h"

#define TEST_SCENE
#include "TestScene.h"
#ifdef TEST_SCENE

#endif

void Game::LoadGame(const GameInfo& gameInfo)
{
#ifdef TEST_SCENE
	gameInfo.pSceneManager->CreateScene(new TestScene("Test", gameInfo));
	gameInfo.pSceneManager->SetActiveGameScene("Test");
#endif
}
