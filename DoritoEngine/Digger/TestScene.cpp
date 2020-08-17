#include "DoritoPCH.h"
#include "TestScene.h"

#include "Renderer.h"

#include "DoritoFactory.h"
#include "PracticalHelpers.h"
#include "PlayerStatsSystem.h"



TestScene::TestScene(const std::string& sceneName, const GameInfo& gameInfo)
	: Scene(sceneName, gameInfo)
	, m_pTextComp(nullptr)
	, m_pScoreComp(nullptr)
	, m_pGameStats(nullptr)
	, m_FPSNb()
{
}

void TestScene::Initialize()
{
	GetSubject()->AddObserver( "PlayerStats", new PlayerStatsSystem() );

	//FPS
	auto pFPS = DoritoFactory::MakeTextObject(this, "FPS: ", "Lingua.otf", 50);
	AddObject(pFPS);

	//Score 
	auto pScore = DoritoFactory::MakeTextObject(this, "Score: ", "Lingua.otf", 50);
	pScore->GetTransform()->SetPosition(300.f,0.f);
	AddObject(pScore);

	//Character
	auto pCharacter = DoritoFactory::MakeCharacter(this, "Digger/digger.png", PlayerControllers::Player1);
	pCharacter->GetTransform()->SetPosition(978, 773);
	pCharacter->GetTransform()->SetScale(0.2f, 0.2f);
	AddObject(pCharacter);

	////Enemy
	//auto pEnemy = DoritoFactory::MakeEnemy(this, "Digger/hobbin.png");
	//pEnemy->GetTransform()->SetPosition(780, 150);
	//pEnemy->GetTransform()->SetScale(0.2f, 0.2f);
	//AddObject(pEnemy);

	//Updating Text
	m_pTextComp = pFPS->GetComponent<TextComponent>();
	m_pScoreComp = pScore->GetComponent<TextComponent>();
	m_pScoreComp->SetColor(sf::Color::Green);

	//Read game stats
	m_pGameStats = static_cast<PlayerStatsSystem*>(GetSubject()->GetObserver("PlayerStats"));
	
	DoritoFactory::MakeLevel(this, "Levels/level-1.json");

	Renderer::GetInstance()->SetDebugRendering(false);
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

