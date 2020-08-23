#include "DoritoPCH.h"
#include "MenuScene.h"
#include "Level1_Scene.h"

#include "DoritoFactory.h"

MenuScene::MenuScene(const std::string& sceneName, const GameInfo& gameInfo)
	: Scene(sceneName, gameInfo)
	, m_pNameScore(nullptr)
{
}

void MenuScene::Initialize()
{
	auto window = GetGameInfo().windowSettings;

	auto pBackground = DoritoFactory::MakeSprite(this, "TitleScreen.png");
	pBackground->GetTransform()->SetPosition(static_cast<float>(window.width / 2),
		static_cast<float>(window.height / 2));
	AddObject(pBackground);

	auto startGame = [this]()
	{
		GetGameInfo().pSceneManager->RemoveScene("Level1");
		
		GetGameInfo().pSceneManager->CreateScene(new Level_1("Level1", GetGameInfo()));

		GetGameInfo().pSceneManager->SetActiveGameScene("Level1");
	};

	GetGameInfo().pInput->AddKeyboardEvent(KeyBoardEvent("START", KeyboardButton::Enter, startGame, InputTriggerState::Pressed));
	GetGameInfo().pInput->AddGamePadActionEvent(GamePadActionEvent("START", GamepadButtons::START, PlayerControllers::Player1, startGame, InputTriggerState::Pressed));
}

void MenuScene::Update(float)
{
}

void MenuScene::Render() const
{
}
