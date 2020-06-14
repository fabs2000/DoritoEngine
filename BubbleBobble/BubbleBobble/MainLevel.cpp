#include "DoritoPCH.h"
#include "MainLevel.h"

#include "DoritoFactory.h"

MainLevel::MainLevel(const std::string& sceneName, const GameInfo& gameInfo)
	: Scene(sceneName, gameInfo)
	, m_pFPS( nullptr )
	, m_pPlayer( nullptr )
	, m_pTextComp( nullptr )
	, m_FPSNb()
{
}

void MainLevel::Initialize()
{
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


	//for (int i{}; )
	auto enemy = DoritoFactory::MakeEnemy(this, "ZenChan.png");
	AddObject(enemy);
	enemy->GetTransform()->Scale(0.3f, 0.3f);
	enemy->GetTransform()->SetPosition(800, 180);

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
