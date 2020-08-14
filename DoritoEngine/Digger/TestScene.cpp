#include "DoritoPCH.h"
#include "TestScene.h"

#include "Renderer.h"

#include "DoritoFactory.h"
#include "PracticalHelpers.h"
#include "PlayerStatsSystem.h"



TestScene::TestScene(const std::string& sceneName, const GameInfo& gameInfo)
	: Scene(sceneName, gameInfo)
	, m_pFPS(nullptr)
	, m_pTextComp(nullptr)
	, m_pScore(nullptr)
	, m_pCharacter(nullptr)
	, m_FPSNb()
{
}

void TestScene::Initialize()
{
	GetSubject()->AddObserver( "PlayerStats", new PlayerStatsSystem() );

	//FPS
	m_pFPS = DoritoFactory::MakeTextObject(this, "FPS: ", "Lingua.otf", 50);
	AddObject(m_pFPS);

	//Score 
	m_pScore = DoritoFactory::MakeTextObject(this, "Score: ", "Lingua.otf", 50);
	m_pScore->GetTransform()->SetPosition(0.f,150.f);
	AddObject(m_pScore);

	m_pCharacter = DoritoFactory::MakeCharacter(this, "Digger/digger.png", PlayerControllers::Player1);
	m_pCharacter->GetTransform()->SetPosition(650, 150);
	m_pCharacter->GetTransform()->SetScale(0.2f, 0.2f);
	AddObject(m_pCharacter);

	auto pEnemy = DoritoFactory::MakeEnemy(this, "Digger/hobbin.png");
	pEnemy->GetTransform()->SetPosition(780, 150);
	pEnemy->GetTransform()->SetScale(0.2f, 0.2f);
	AddObject(pEnemy);

	m_pTextComp = m_pFPS->GetComponent<TextComponent>();
	m_pScoreComp = m_pScore->GetComponent<TextComponent>();
	m_pScoreComp->SetColor(sf::Color::Green);

	m_pGameStats = static_cast<PlayerStatsSystem*>(GetSubject()->GetObserver("PlayerStats"));

	Renderer::GetInstance()->SetDebugRendering(true);
}

void TestScene::Update(float dt)
{
	m_FPSNb = int(1 / dt);
	m_pTextComp->SetText("FPS: " + std::to_string(m_FPSNb));

	m_pScoreComp->SetText("Score: " + std::to_string(m_pGameStats->GetScore()));
}

void TestScene::Render() const
{
}

