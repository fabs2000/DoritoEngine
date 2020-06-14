#include "DoritoPCH.h"
#include "MainLevel.h"

#include "DoritoFactory.h"
#include "PracticalHelpers.h"


MainLevel::MainLevel(const std::string& sceneName, const GameInfo& gameInfo)
	: Scene(sceneName, gameInfo)
	, m_pFPS( nullptr )
	, m_pPlayer( nullptr )
	, m_pTextComp( nullptr )
	, m_FPSNb()
	, m_2PlayerMode(false)
{
}

void MainLevel::Initialize()
{
	auto join = std::bind(&MainLevel::AddPlayer2, this);

	GetGameInfo().pInput->AddGamePadEvent(GamePadEvent("Jump", GamepadButtons::START, 
		PlayerControllers::Player2, join, InputTriggerState::Pressed));

	//Map
	auto map = DoritoFactory::MakeLevel(this, "Map.png", "level1.json");
	map->GetTransform()->SetPosition(
		float(GetGameInfo().windowSettings.width / 2), 
		float(GetGameInfo().windowSettings.height / 2)
	);
	map->GetTransform()->Scale(2.8f, 2.8f);
	AddObject(map);

	//Player
	m_pPlayer = DoritoFactory::MakeCharacter(this, "Bub.png", PlayerControllers::Player1);

	m_pPlayer->GetTransform()->SetPosition(650, 150);
	m_pPlayer->GetTransform()->Scale(0.3f,0.3f);
	AddObject(m_pPlayer);



	auto enemies = DoritoHelpers::ReadJson("enemies.json");

	for (auto& enemyInfo : enemies["Enemies"])
	{
		auto enemy = DoritoFactory::MakeEnemy(this, enemyInfo["Texture"]);
		AddObject(enemy);
		enemy->GetTransform()->Scale(0.3f, 0.3f);
		enemy->GetTransform()->SetPosition(enemyInfo["X"], enemyInfo["Y"]);
	}

	//FPS
	m_pFPS = DoritoFactory::MakeTextObject(this, "FPS: ", "Lingua.otf", 50);
	AddObject(m_pFPS);

	m_pTextComp = m_pFPS->GetComponent<TextComponent>();
}

void MainLevel::Update(float dt)
{
	m_FPSNb = int(1 / dt);
	m_pTextComp->SetText("FPS: " + std::to_string(m_FPSNb));
}

void MainLevel::Render() const
{
}

void MainLevel::AddPlayer2()
{

	std::cout << "YES\n";\
	if (!m_2PlayerMode)
	{
		//Player
		m_pPlayer = DoritoFactory::MakeCharacter(this, "Bob.png", PlayerControllers::Player2);
		m_pPlayer->GetTransform()->SetPosition(650, 150);
		m_pPlayer->GetTransform()->Scale(0.3f, 0.3f);
		AddObject(m_pPlayer);

		m_2PlayerMode = true;
	}
}
