#include "DoritoPCH.h"
#include "TestScene.h"

#include "Renderer.h"

#include "DoritoFactory.h"
#include "PracticalHelpers.h"

TestScene::TestScene(const std::string& sceneName, const GameInfo& gameInfo)
	: Scene(sceneName, gameInfo)
	, m_pTextComp(nullptr)
	, m_FPSNb()
{
}

void TestScene::Initialize()
{
	//FPS
	auto pFPS = DoritoFactory::MakeTextObject(this, "FPS: ", "Lingua.otf", 50);
	AddObject(pFPS);
	 
	//auto pEnemy = DoritoFactory::MakeEnemyBase(this, "Digger/hobbin.png");
	//pEnemy->GetTransform()->SetPosition(300, 250);
	//pEnemy->GetTransform()->SetScale(0.2f, 0.2f);
	//AddObject(pEnemy);


	//Enemy
	DoritoFactory::MakeEnemy(this, "Digger/hobbin.png", sf::Vector2f(700, 250));


	//Character
	auto pCharacter = DoritoFactory::MakeCharacter(this, "Digger/digger.png", PlayerControllers::Player1);
	pCharacter->GetTransform()->SetPosition(978, 773);
	pCharacter->GetTransform()->SetScale(0.2f, 0.2f);
	AddObject(pCharacter);

	//Test Chunks
	DoritoFactory::MakeDirtChunk(this, sf::Vector2f(300, 400), "Digger/dirt_center.png", ChunkType::DIRT);
	DoritoFactory::MakeDirtChunk(this, sf::Vector2f(300, 810), "Digger/dirt_center.png", ChunkType::DIRT);
	DoritoFactory::MakeDirtChunk(this, sf::Vector2f(402, 810), "Digger/dirt_center.png", ChunkType::DIRT);
	DoritoFactory::MakeDirtChunk(this, sf::Vector2f(504, 810), "Digger/dirt_center.png", ChunkType::DIRT);
	DoritoFactory::MakeDirtChunk(this, sf::Vector2f(606, 810), "Digger/dirt_center.png", ChunkType::DIRT);
	DoritoFactory::MakeDirtChunk(this, sf::Vector2f(708, 708), "Digger/dirt_center.png", ChunkType::DIRT);
	DoritoFactory::MakeDirtChunk(this, sf::Vector2f(606, 708), "Digger/dirt_center.png", ChunkType::DIRT);

	//Gold Bag
	auto pGold = DoritoFactory::MakeGoldBag(this, "Digger/gold.png");
	pGold->GetTransform()->SetScale(0.2f,0.2f);
	pGold->GetTransform()->SetPosition(300, 300);
	AddObject(pGold);

	pGold = DoritoFactory::MakeGoldBag(this, "Digger/gold.png");
	pGold->GetTransform()->SetScale(0.2f, 0.2f);
	pGold->GetTransform()->SetPosition(504, 100);
	AddObject(pGold);

	m_pTextComp = pFPS->GetComponent<TextComponent>();

	Renderer::GetInstance()->SetDebugRendering(true);
}

void TestScene::Update(float dt)
{
	m_FPSNb = int(1 / dt);
	m_pTextComp->SetText("FPS: " + std::to_string(m_FPSNb));
}

void TestScene::Render() const
{
}
