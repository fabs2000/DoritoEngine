#include "DoritoPCH.h"
#include "TestScene.h"

#include "DoritoFactory.h"

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
	m_pRATTLED = DoritoFactory::MakeSpriteObject("rattled.jpg");
	AddObject(m_pRATTLED);

	m_pFPS = DoritoFactory::MakeTextObject("FPS: ", "Lingua.otf", 50);
	AddObject(m_pFPS);

	m_pTextComp = m_pFPS->GetComponent<TextComponent>();
}

void TestScene::Update(float dt)
{
	m_pRATTLED->GetTransform()->SetPosition(650, 360);
	//m_pRATTLED->GetTransform()->Rotate(dt, true);

	//m_pRATTLED->GetTransform()->Move(dt * 10, dt * 10);

	m_FPSNb = int(1 / dt);
	m_pTextComp->SetText("FPS: " + std::to_string(m_FPSNb));
}

void TestScene::Render() const
{
}
