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
	, m_EnemySpawnTimer(6.f)
{
}

void Level_1::Initialize()
{
#pragma region CONSTAT_ACROSS_LEVELS
	GetSubject()->AddObserver("PlayerStats", new PlayerStatsSystem(19, 5));

	//FPS
	auto pFPS = DoritoFactory::MakeTextObject(this, "FPS: ", "Lingua.otf", 50);
	AddObject(pFPS);

	//HUD
	auto pHUD = DoritoFactory::MakeHUD(this);
	pHUD->GetTransform()->SetPosition(300.f, 0.f);
	AddObject(pHUD);

	//Character
	m_pDigger = DoritoFactory::MakeDigger(this, "digger.png", PlayerControllers::Player1);
	m_pDigger->GetTransform()->SetPosition(978, 773);
	m_pDigger->GetTransform()->SetScale(0.2f, 0.2f);
	AddObject(m_pDigger);


	//Updating Text
	m_pTextComp = pFPS->GetComponent<TextComponent>();
	m_pGameStats = static_cast<PlayerStatsSystem*>(GetSubject()->GetObserver("PlayerStats"));

#pragma endregion 

	//LEVEL 1 INFO
	DoritoFactory::MakeLevel(this, "level-1.json");

	m_MaxEnemies = m_pGameStats->GetEnemyCount();

	//Enemy
	auto enemy = DoritoFactory::MakeEnemyBase(this, "nobbin.png");
	enemy->GetTransform()->SetPosition(1479, 767);
	enemy->GetTransform()->SetScale(0.2f, 0.2f);
	AddObject(enemy);

	Renderer::GetInstance()->SetDebugRendering(true);
}

void Level_1::Update(float dt)
{
	//FPS
	m_FPSNb = int(1 / dt);
	m_pTextComp->SetText("FPS: " + std::to_string(m_FPSNb));

	//if(m_EnemySpawnTimer > 0.f)
	//	m_EnemySpawnTimer -= dt;
	//if (m_EnemySpawnTimer <= 0.f && m_EnemyCount < m_MaxEnemies)
	//{
	//	auto enemy = DoritoFactory::MakeEnemyBase(this, "nobbin.png");
	//	enemy->GetTransform()->SetPosition(1479, 257);
	//	enemy->GetTransform()->SetScale(0.2f, 0.2f);
	//	AddObject(enemy);
	//	m_EnemyCount++;
	//	m_EnemySpawnTimer = 6.f;
	//}

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
			DoritoFactory::MakeLevel(this, "level-2.json");
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
			DoritoFactory::MakeLevel(this, "level-3.json");
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
