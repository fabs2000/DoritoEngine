#include "DoritoPCH.h"
#include "HUDComponent.h"
#include "Scene.h"
#include "Renderer.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "PlayerStatsSystem.h"
#include "SpriteComponent.h"

#include "DoritoFactory.h"

HUDComponent::HUDComponent()
	: m_pTextComp(nullptr)
	, m_pScoreComp(nullptr)
	, m_pLivesSprite()
	, m_pSceneRef(nullptr)
	, m_pGameStats(nullptr)
{
}

void HUDComponent::Initialize()
{
	m_pSceneRef = GetGameObject()->GetScene();

	m_pScoreComp = GetGameObject()->GetComponent<TextComponent>();
	m_pScoreComp->SetColor(sf::Color::Green);
	m_pGameStats = static_cast<PlayerStatsSystem*>(m_pSceneRef->GetSubject()->GetObserver("PlayerStats"));

	float xPos = 650.f, offset = 80.f;

	for (int32_t i{}; i < m_pGameStats->GetLives(); i++)
	{
		auto sprite = DoritoFactory::MakeSprite(m_pSceneRef, "Digger/digger.png");
		m_pLivesSprite.push_back(sprite->GetComponent<SpriteComponent>());

		sprite->GetTransform()->SetScale(0.2f, 0.2f);
		xPos += offset;
		sprite->GetTransform()->SetPosition(xPos, 30);

		m_pSceneRef->AddObject(sprite);
	}
}

void HUDComponent::Update(float)
{
	m_pScoreComp->SetText("Score: " + std::to_string(m_pGameStats->GetScore()));

	m_pGameStats->Update();
}

void HUDComponent::Render()
{
	//Draw as many diggers as lives each frame, losing lives auto decreases them.
	if (m_pGameStats->GetLives() >= 0)
	{
		auto id = m_pGameStats->GetLives();

		//std::cout << "Lives: " << id << "\n";

		if (m_pGameStats->GetLostLife())
		{
			m_pLivesSprite[id]->SetCanRender(false);
		}
		else if (m_pGameStats->GetGainedLife())
		{
			//Why this needs to be done --->>>
			//https://docs.microsoft.com/es-es/cpp/code-quality/c26451?view=vs-2019
			m_pLivesSprite[id - static_cast<__int64>(1)]->SetCanRender(true);
		}
	}
}
