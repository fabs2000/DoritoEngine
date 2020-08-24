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
	, m_pEnemyPlayer(nullptr)
	, m_FPSNb()
	, m_GameState(LevelState::LEVEL_1)
	, m_EnemySpawnTimer(7.f)
	, m_MaxEnemies()
	, m_EnemyCount()
	, m_EnemySpawnPos(1479, 257)
	, m_FirstLevelInit(false)
	, m_SecondPlayerJoined(false)
{
}

void Level_1::Initialize()
{
#pragma region CONSTAT_ACROSS_LEVELS
	GetSubject()->AddObserver("PlayerStats", new PlayerStatsSystem(19, 5));

	//FPS
	auto pFPS = DoritoFactory::MakeTextObject(this, "FPS: ", "Lingua.otf", 50);
	AddObject(pFPS);

	//Character
	m_pDigger = DoritoFactory::MakeDigger(this, "digger.png", PlayerControllers::Player1);
	m_pDigger->GetTransform()->SetPosition(978, 773);
	m_pDigger->GetTransform()->SetScale(0.2f, 0.2f);
	AddObject(m_pDigger);


	//Updating Text
	m_pTextComp = pFPS->GetComponent<TextComponent>();
	m_pGameStats = static_cast<PlayerStatsSystem*>(GetSubject()->GetObserver("PlayerStats"));

#pragma endregion 
	//Join game
	//THIS CRASHES DONT CONNECT CONTROLLER 2
	auto join = [this]()
	{
		if (!m_SecondPlayerJoined)
		{
			auto enemies = GetObjectsWithEitherTag("Nobbin", "Hobbin");
			int randId;

			if (enemies.size() != 0)
			{
				randId = DoritoMath::Rand(0, static_cast<int>(enemies.size()) - 1);
				auto enemy = enemies[randId];
				
				if (enemy->GetTag() == "Nobbin")
				{
					enemy->AddComponentUpd(
						new EntityControllerComponent(PlayerControllers::Player2, 80.f));
				}
				else if (enemy->GetTag() == "Hobbin")
				{
					enemy->AddComponentUpd(
						new EntityControllerComponent(PlayerControllers::Player2, 120.f));
				}

				enemy->GetComponent<EnemyComponent>()->SetControlledByPlayer(true);

				m_pEnemyPlayer = enemy;
				m_SecondPlayerJoined = true;
			}
			else
				std::cout << "No Enemies to control\n";
		}
		else
			std::cout << "Enemy already selected\n";
	};
	GetGameInfo().pInput->AddGamePadActionEvent(GamePadActionEvent("2ndPlayerJoin", GamepadButtons::A, PlayerControllers::Player2, join, InputTriggerState::Pressed));

	Renderer::GetInstance()->SetDebugRendering(false);
}

void Level_1::Update(float dt)
{
	//FPS
	m_FPSNb = static_cast<int>(1 / dt);
	m_pTextComp->SetText("FPS: " + std::to_string(m_FPSNb));

	//Enemy Check
	if (m_pEnemyPlayer != nullptr)
	{
		if (m_pEnemyPlayer->GetMarkedForDelete())
		{
			m_pEnemyPlayer = nullptr;
			m_SecondPlayerJoined = false;
		}
	}

	//INIT LEVEL 1
	if (!m_FirstLevelInit)
	{
		//LEVEL 1 INFO
		DoritoFactory::MakeLevel(this, "level-1.json");
		m_MaxEnemies = m_pGameStats->GetEnemyCount();

		//HUD
		auto pHUD = DoritoFactory::MakeHUD(this);
		pHUD->GetTransform()->SetPosition(300.f, 0.f);
		AddObject(pHUD);

		m_FirstLevelInit = true;
	}

	//Enemy Spawner
	EnemySpawner(dt);

	//Check for game over
	if (m_pGameStats->GetIsGameOver())
	{
		ResetToLevel1();

		GetGameInfo().pSceneManager->SetActiveGameScene("Menu");
	}

	//Checks states of Game
	switch (m_GameState)
	{
	case LevelState::LEVEL_1:

		if (m_pGameStats->GetEmeraldCount() == 0 || m_pGameStats->GetEnemyCount() == 0)
		{
			SetLevel2();
		}
		break;

	case LevelState::LEVEL_2:

		if (m_pGameStats->GetEmeraldCount() == 0 || m_pGameStats->GetEnemyCount() == 0)
		{
			SetLevel3();
		}
		break;

	case LevelState::LEVEL_3:
		if (m_pGameStats->GetEmeraldCount() == 0 || m_pGameStats->GetEnemyCount() == 0)
		{
			ResetToLevel1();

			GetGameInfo().pSceneManager->SetActiveGameScene("Menu");
		}

		break;
	}
}

void Level_1::Render() const
{
}

void Level_1::ResetToLevel1()
{
	ClearObjectsWithTag("Dirt");
	ClearObjectsWithTag("Gold");

	//Enemies need to be cleared when there are enemies
	ClearObjectsWithTag("Nobbin");
	ClearObjectsWithTag("Hobbin");

	ClearObjectsWithTag("HUD");

	m_EnemyCount = 0;
	m_MaxEnemies = m_pGameStats->GetEnemyCount();
	m_EnemySpawnPos = sf::Vector2f(1479, 257);
	m_EnemySpawnTimer = 6.f;

	//Write score to file
	std::ofstream file;
	file.open("../Resources/Scores.txt", std::ios_base::app);
	file << m_pGameStats->GetScore() << "\n";
	file.close();

	//Reset to level 1
	GetSubject()->Notify(6);
	m_GameState = LevelState::LEVEL_1;

	m_pDigger->GetTransform()->SetPosition(978, 773);
	m_pDigger->GetComponent<DiggerComponent>()->SetState(DiggerState::MOVING);
	m_FirstLevelInit = false;
	m_SecondPlayerJoined = false;
}

void Level_1::SetLevel2()
{
	ClearObjectsWithTag("Dirt");
	ClearObjectsWithTag("Gold");

	//Enemies need to be cleared when there are enemies
	ClearObjectsWithTag("Nobbin");
	ClearObjectsWithTag("Hobbin");

	GetSubject()->Notify(7);
	m_GameState = LevelState::LEVEL_2;

	m_EnemyCount = 0;
	m_MaxEnemies = m_pGameStats->GetEnemyCount();
	m_EnemySpawnPos = sf::Vector2f(1173, 767);
	m_EnemySpawnTimer = 6.f;

	m_pDigger->GetTransform()->SetPosition(978, 773);
	DoritoFactory::MakeLevel(this, "level-2.json");
}

void Level_1::SetLevel3()
{
	ClearObjectsWithTag("Dirt");
	ClearObjectsWithTag("Gold");

	//Enemies need to be cleared when there are enemies
	ClearObjectsWithTag("Nobbin");
	ClearObjectsWithTag("Hobbin");

	GetSubject()->Notify(8);
	m_GameState = LevelState::LEVEL_3;

	m_EnemyCount = 0;
	m_MaxEnemies = m_pGameStats->GetEnemyCount();
	m_EnemySpawnPos = sf::Vector2f(1377, 257);
	m_EnemySpawnTimer = 6.f;

	m_pDigger->GetTransform()->SetPosition(978, 773);

	DoritoFactory::MakeLevel(this, "level-3.json");
}

void Level_1::EnemySpawner(float dt)
{
	if (m_EnemySpawnTimer > 0.f)
		m_EnemySpawnTimer -= dt;

	if (m_EnemySpawnTimer <= 0.f && m_EnemyCount < m_MaxEnemies)
	{
		auto enemy = DoritoFactory::MakeEnemyBase(this, "nobbin.png", m_EnemySpawnPos);
		enemy->GetTransform()->SetPosition(m_EnemySpawnPos);
		enemy->GetTransform()->SetScale(0.2f, 0.2f);
		AddObject(enemy);
		m_EnemyCount++;
		m_EnemySpawnTimer = 6.f;
	}
}
