#include "DoritoPCH.h"
#include "Menu.h"

#include "DoritoFactory.h"

MenuScene::MenuScene(const std::string& sceneName, const GameInfo& gameInfo)
	: Scene(sceneName, gameInfo)
{
}

void MenuScene::Initialize()
{
	auto menu = DoritoFactory::MakeSprite(this, "Menu.png");
	AddObject(menu);

	menu->GetTransform()->SetPosition(
		float(GetGameInfo().windowSettings.width / 2),
		float(GetGameInfo().windowSettings.height / 2)
	);

	menu->GetTransform()->Scale(0.8f,0.7f);

	auto start = std::bind(&MenuScene::StartGame, this);

	GetGameInfo().pInput->AddKeyboardEvent(KeyBoardEvent("START", KeyboardButton::Enter, start, InputTriggerState::Pressed));
	GetGameInfo().pInput->AddGamePadEvent(GamePadEvent("START", GamepadButtons::START, PlayerControllers::Player1, start, InputTriggerState::Pressed));
}

void MenuScene::Update(float dt)
{
	dt;
}

void MenuScene::Render() const
{
}

void MenuScene::StartGame()
{
	GetGameInfo().pSceneManager->SetActiveGameScene("Main");
}