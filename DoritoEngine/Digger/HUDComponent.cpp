#include "DoritoPCH.h"
#include "HUDComponent.h"
#include "Scene.h"
#include "Renderer.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "PlayerStatsSystem.h"
#include "SpriteComponent.h"

#include "DoritoFactory.h"

HUDComponent::HUDComponent()
{
}

void HUDComponent::Initialize()
{
	m_pSceneRef = GetGameObject()->GetScene();

	m_pScoreComp = GetGameObject()->GetComponent<TextComponent>();
	m_pGameStats = static_cast<PlayerStatsSystem*>(m_pSceneRef->GetSubject()->GetObserver("PlayerStats"));

	float xPos = 500.f, offset = 80.f;

	for (uint32_t i{}; i < m_Lives; i++)
	{
		auto sprite = DoritoFactory::MakeSprite(m_pSceneRef, "Digger/digger.png");
		m_pSceneRef->AddObject(sprite);
		sprite->GetTransform()->SetScale(0.2f, 0.2f);
		xPos += offset;
		sprite->GetTransform()->SetPosition(xPos, 50);
	}
}

void HUDComponent::Update(float)
{
	m_pScoreComp->SetText("Score: " + std::to_string(m_pGameStats->GetScore()));
}

void HUDComponent::Render()
{

}
