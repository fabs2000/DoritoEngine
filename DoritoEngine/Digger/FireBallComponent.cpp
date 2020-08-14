#include "DoritoPCH.h"

#include "FireBallComponent.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "Scene.h"
#include "EnemyComponent.h"

FireBallComponent::FireBallComponent(const sf::Vector2f& direction)
	: m_Velocity(0.f, 0)
	, m_Direction(direction)
	, m_Speed(450.f)

	, m_pCollider(nullptr)
{
}

void FireBallComponent::Initialize()
{
	m_pCollider = GetGameObject()->GetComponent<ColliderComponent>();

	if (m_pCollider->GetIsTrigger())
	{
		HandleInTrigger();
	}
}

void FireBallComponent::Update(float dt)
{
	m_Velocity = m_Direction * m_Speed;

	m_Velocity = m_Velocity * dt;

	GetParentTransform()->Move(m_Velocity);
}

void FireBallComponent::Render()
{
}

void FireBallComponent::HandleInTrigger()
{
	auto killEnemy = [this](GameObject*, GameObject* other)->void
	{
		if (other->GetTag() == "Enemy")
		{
			auto comp = other->GetComponent<EnemyComponent>();

			if (comp)
			{
				other->Delete();
				GetGameObject()->GetScene()->GetSubject()->Notify(1);
			}
		}
	};

	m_pCollider->SetTriggerCallback(killEnemy);
}
