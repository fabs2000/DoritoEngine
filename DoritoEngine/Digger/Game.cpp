#include "DoritoPCH.h"
#include "Game.h"

#include "Scene.h"

#define GAME
//#define TEST_SCENE

#ifdef GAME
#include "Level1_Scene.h"
#include "MenuScene.h"

#endif

#ifdef TEST_SCENE
#include "TestScene.h"
#endif 


void Game::LoadGame(const GameInfo& gameInfo)
{
#ifdef TEST_SCENE
	gameInfo.pSceneManager->CreateScene(new TestScene("TestScene", gameInfo));
	gameInfo.pSceneManager->SetActiveGameScene("TestScene");
#endif // TEST_SCENE


#ifdef GAME
	gameInfo.pSceneManager->CreateScene(new MenuScene("Menu", gameInfo));
	gameInfo.pSceneManager->CreateScene(new Level_1("Level1", gameInfo));
	gameInfo.pSceneManager->SetActiveGameScene("Menu");
#endif
}
