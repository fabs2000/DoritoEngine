#include "DoritoPCH.h"
#include "TestScene.h"

#include "DoritoFactory.h"

#include <istream>


TestScene::TestScene(const std::string& sceneName, const GameInfo& gameInfo)
	: Scene(sceneName, gameInfo)
	, m_pFPS( nullptr )
	, m_pRATTLED( nullptr )
	, m_pTextComp( nullptr )
	, m_FPSNb()
{
}

void TestScene::Initialize()
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
	m_pRATTLED = DoritoFactory::MakeCharacter(this, "Bub.png", PlayerControllers::Player1);
	m_pRATTLED->SetTag("Physics");
	m_pRATTLED->GetTransform()->SetPosition(650, 150);
	m_pRATTLED->GetTransform()->Scale(0.3f,0.3f);
	AddObject(m_pRATTLED);

	//FPS
	m_pFPS = DoritoFactory::MakeTextObject(this, "FPS: ", "Lingua.otf", 50);
	AddObject(m_pFPS);

	m_pTextComp = m_pFPS->GetComponent<TextComponent>();
}

void TestScene::Update(float dt)
{
	m_FPSNb = int(1 / dt);
	m_pTextComp->SetText("FPS: " + std::to_string(m_FPSNb));
}

void TestScene::Render() const
{
}
