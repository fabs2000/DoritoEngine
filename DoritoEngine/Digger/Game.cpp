#include "DoritoPCH.h"
#include "Game.h"

#include "Scene.h"

#define LEVEL_1
#define TEST_SCENE

#ifdef LEVEL_1
#include "Level1_Scene.h"
#endif



#ifdef TEST_SCENE
#endif 


void Game::LoadGame(const GameInfo& gameInfo)
{
#ifdef LEVEL_1
	gameInfo.pSceneManager->CreateScene(new Level_1("Level1", gameInfo));
	gameInfo.pSceneManager->SetActiveGameScene("Level1");
#endif
}
