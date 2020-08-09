#include "DoritoPCH.h"
#include "TestScene.h"

#include "DoritoFactory.h"
#include "PracticalHelpers.h"


TestScene::TestScene(const std::string& sceneName, const GameInfo& gameInfo)
	: Scene(sceneName, gameInfo)
	, m_pFPS(nullptr)
	, m_pTextComp(nullptr)
	, m_FPSNb()
{
}

void TestScene::Initialize()
{
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
