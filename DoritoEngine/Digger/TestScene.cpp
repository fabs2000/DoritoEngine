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

	m_pCharacter = DoritoFactory::MakeCharacter(this, "digger.png", PlayerControllers::Player1);
	m_pCharacter->GetTransform()->SetPosition(650, 150);
	m_pCharacter->GetTransform()->SetScale(0.2f, 0.2f);
	AddObject(m_pCharacter);

	m_pTextComp = m_pFPS->GetComponent<TextComponent>();

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

void TestScene::InitInput()
{
	auto leftTest = [this](const sf::Vector2f& scale)->void
	{
		std::cout << "Left Stick X: " << scale.x << ", Left Stick Y: " << scale.y << "\n";
	};

	auto rightTest = [this](const sf::Vector2f& scale)->void
	{
		std::cout << "Right Stick X: " << scale.x << ", Right Stick Y: " << scale.y << "\n";
	};

	auto buttonTest = [this]()->void
	{
		std::cout << "Pressed Button\n";
	};

	GetGameInfo().pInput->AddGamePadAxisEvent(GamePadAxisEvent("LeftTest", L_STICK, PlayerControllers::Player1, leftTest));
	GetGameInfo().pInput->AddGamePadAxisEvent(GamePadAxisEvent("RightTest", R_STICK, PlayerControllers::Player1, rightTest));

	GetGameInfo().pInput->AddGamePadActionEvent(GamePadActionEvent("X", A, PlayerControllers::Player1, buttonTest));
	GetGameInfo().pInput->AddGamePadActionEvent(GamePadActionEvent("O", B, PlayerControllers::Player1, buttonTest, InputTriggerState::Pressed));
	GetGameInfo().pInput->AddGamePadActionEvent(GamePadActionEvent("SQUARE", X, PlayerControllers::Player1, buttonTest, InputTriggerState::Released));
}
