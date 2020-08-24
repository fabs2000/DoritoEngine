#include "DoritoPCH.h"
#include "MenuScene.h"
#include "Level1_Scene.h"

#include "DoritoFactory.h"

MenuScene::MenuScene(const std::string& sceneName, const GameInfo& gameInfo)
	: Scene(sceneName, gameInfo)
	, m_pNamesScores(std::vector<TextComponent*>())
	, m_AllScores(std::vector<int>(10))
	, m_InitScores(true)
{
}

void MenuScene::Initialize()
{
	//INIT Background
	auto window = GetGameInfo().windowSettings;
	auto pBackground = DoritoFactory::MakeSprite(this, "TitleScreen.png");
	pBackground->GetTransform()->SetPosition(static_cast<float>(window.width / 2),
		static_cast<float>(window.height / 2));
	AddObject(pBackground);

	//Scores
	float yPos = 200.f
		, xPos = 60.f
		, offset = 100.f;


	//Create Score Boxes
	for (int i{}; i < 10; i++)
	{
		if (i == 5)
		{
			xPos = 420.f;
			yPos = 200.f;
		}

		auto score = DoritoFactory::MakeTextObject(this,  std::to_string(i) + "_ _ _ | ________", "Lingua.otf", 50);
		score->GetTransform()->SetPosition(xPos, yPos);
		AddObject(score);

		m_pNamesScores.push_back(score->GetComponent<TextComponent>());

		yPos += offset;
	}

	//Begin Game Action
	auto startGame = [this]()
	{
		if (!GetGameInfo().pSceneManager->IsActiveScene("Level1"))
		{
			GetGameInfo().pSceneManager->GetScene("Level1")->ClearObjectsWithTag("Dirt");
		}

		GetGameInfo().pSceneManager->SetActiveGameScene("Level1");

		m_InitScores = true;
	};

	GetGameInfo().pInput->AddKeyboardEvent(KeyBoardEvent("START", KeyboardButton::Enter, startGame, InputTriggerState::Pressed));
	GetGameInfo().pInput->AddGamePadActionEvent(GamePadActionEvent("START", GamepadButtons::START, PlayerControllers::Player1, startGame, InputTriggerState::Pressed));
}

void MenuScene::Update(float)
{
	if (m_InitScores)
	{
		//Read in scores
		std::ifstream file;
		std::string line;
		file.open("../Resources/Scores.txt");
		if (file.is_open())
		{
			while (getline(file, line))
			{
				if (line.size() != 0)
				{
					int score = std::stoi(line);
					if(std::find(m_AllScores.begin(), m_AllScores.end(), score) == m_AllScores.end())
						m_AllScores.push_back(score);
				}
			}
		}

		//Order in descending order
		std::sort(m_AllScores.begin(), m_AllScores.end(), std::greater<int>());

		for (int i{}; i < 10; i++)
		{
			m_pNamesScores[i]->SetText( "_ _ _ | " + std::to_string(m_AllScores[i]));
		}
	
		m_InitScores = false;
	}
}

void MenuScene::Render() const
{
}
