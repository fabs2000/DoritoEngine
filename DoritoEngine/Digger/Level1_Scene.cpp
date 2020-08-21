#include "DoritoPCH.h"
#include "Level1_Scene.h"

#include "Renderer.h"

#include "DoritoFactory.h"
#include "PracticalHelpers.h"
#include "PlayerStatsSystem.h"

Level_1::Level_1(const std::string& sceneName, const GameInfo& gameInfo)
	: Scene(sceneName, gameInfo)
	, m_pTextComp(nullptr)
	, m_pScoreComp(nullptr)
	, m_pGameStats(nullptr)
	, m_FPSNb()
{
}

void Level_1::Initialize()
{
	GetSubject()->AddObserver( "PlayerStats", new PlayerStatsSystem() );

	//FPS
	auto pFPS = DoritoFactory::MakeTextObject(this, "FPS: ", "Lingua.otf", 50);
	AddObject(pFPS);

	//Score 
	//auto pScore = DoritoFactory::MakeTextObject(this, "Score: ", "Lingua.otf", 50);
	//pScore->GetTransform()->SetPosition(300.f,0.f);
	//AddObject(pScore);

	//HUD
	auto pHUD = DoritoFactory::MakeHUD(this);
	pHUD->GetTransform()->SetPosition(300.f, 0.f);
	AddObject(pHUD);

	//Character
	auto pCharacter = DoritoFactory::MakeDigger(this, "Digger/digger.png", PlayerControllers::Player1);
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

	DoritoFactory::MakeLevel(this, "Levels/level-1.json");

	Renderer::GetInstance()->SetDebugRendering(false);
}

void Level_1::Update(float dt)
{
	m_FPSNb = int(1 / dt);
	m_pTextComp->SetText("FPS: " + std::to_string(m_FPSNb));
}

void Level_1::Render() const
{
}

