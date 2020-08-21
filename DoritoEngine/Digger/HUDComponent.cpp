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

	for (uint32_t i{}; i < m_pGameStats->GetLives(); i++)
	{
		auto sprite = DoritoFactory::MakeSprite(m_pSceneRef, "Digger/digger.png");
		m_pLivesSprite.push_back(sprite->GetComponent<SpriteComponent>());

		sprite->GetTransform()->SetScale(0.2f, 0.2f);
		xPos += offset;
		sprite->GetTransform()->SetPosition(xPos, 30);

		m_pSceneRef->AddObject(sprite);
	}

	m_pLivesSprite;
}

void HUDComponent::Update(float)
{
	m_pScoreComp->SetText("Score: " + std::to_string(m_pGameStats->GetScore()));

	m_pGameStats->Update();
}

void HUDComponent::Render()
{
	//Draw as many diggers as lives each frame, losing lives auto decreases them.
	if (m_pGameStats->GetLives() < 3)
	{
		m_pLivesSprite[m_pGameStats->GetLives()]->SetCanRender(false);
	}

	std::cout << m_pGameStats->GetLives() << "\n";
}
