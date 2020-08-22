#include "DoritoPCH.h"
#include "Level1_Scene.h"

#include "Renderer.h"

#include "DoritoFactory.h"
#include "PracticalHelpers.h"
#include "PlayerStatsSystem.h"

Level_1::Level_1(const std::string& sceneName, const GameInfo& gameInfo)
	: Scene(sceneName, gameInfo)
	, m_pTextComp(nullptr)
	, m_pGameStats(nullptr)
	, m_pDigger(nullptr)
	, m_FPSNb()
	, m_LevelState(LevelState::LEVEL_1)
{
}

void Level_1::Initialize()
{
#pragma region CONSTAT_ACROSS_LEVELS
	GetSubject()->AddObserver("PlayerStats", new PlayerStatsSystem(19, 1));
	m_pGameStats = static_cast<PlayerStatsSystem*>(GetSubject()->GetObserver("PlayerStats"));

	//FPS
	auto pFPS = DoritoFactory::MakeTextObject(this, "FPS: ", "Lingua.otf", 50);
	AddObject(pFPS);

	//HUD
	auto pHUD = DoritoFactory::MakeHUD(this);
	pHUD->GetTransform()->SetPosition(300.f, 0.f);
	AddObject(pHUD);

	//Character
	m_pDigger = DoritoFactory::MakeDigger(this, "Digger/digger.png", PlayerControllers::Player1);
	m_pDigger->GetTransform()->SetPosition(978, 773);
	m_pDigger->GetTransform()->SetScale(0.2f, 0.2f);
	AddObject(m_pDigger);

	//Updating Text
	m_pTextComp = pFPS->GetComponent<TextComponent>();

#pragma endregion 

	//LEVEL 1
	DoritoFactory::MakeLevel(this, "Levels/level-1.json");

	Renderer::GetInstance()->SetDebugRendering(false);
}

void Level_1::Update(float dt)
{
	//FPS
	m_FPSNb = int(1 / dt);
	m_pTextComp->SetText("FPS: " + std::to_string(m_FPSNb));

	if (m_pGameStats->GetIsGameOver())
	{
		//ClearAllObjects();

		GetGameInfo().pSceneManager->SetActiveGameScene("Menu");
	}

	switch (m_LevelState)
	{
	case LevelState::LEVEL_1:

		if (m_pGameStats->GetEmeraldCount() == 0 || m_pGameStats->GetEnemyCount() == 0)
		{
			ClearObjectsWithTag("Dirt");
			ClearObjectsWithTag("Gold");
			
			//Enemies need to be cleared when there are enemies


			GetSubject()->Notify(6);
			m_LevelState = LevelState::LEVEL_2;

			m_pDigger->GetTransform()->SetPosition(978, 773);

			DoritoFactory::MakeLevel(this, "Levels/level-2.json");
		}
		break;

	case LevelState::LEVEL_2:

		if (m_pGameStats->GetEmeraldCount() == 0 || m_pGameStats->GetEnemyCount() == 0)
		{
			ClearObjectsWithTag("Dirt");
			ClearObjectsWithTag("Gold");

			//Enemies need to be cleared when there are enemies

			GetSubject()->Notify(7);
			m_LevelState = LevelState::LEVEL_3;

			m_pDigger->GetTransform()->SetPosition(978, 773);
			DoritoFactory::MakeLevel(this, "Levels/level-1.json");
		}
		break;

	case LevelState::LEVEL_3:
		//Load victory screen or menu whatever
		if (m_pGameStats->GetEmeraldCount() == 0 || m_pGameStats->GetEnemyCount() == 0)
		{
			GetGameInfo().pSceneManager->SetActiveGameScene("Menu");
		}

		break;
	}
}

void Level_1::Render() const
{
}
