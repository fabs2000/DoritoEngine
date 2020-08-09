#include "DoritoPCH.h"

#include "BubbleComponent.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "Scene.h"
#include "AIController.h"

BubbleComponent::BubbleComponent(float direction)
	: m_Velocity(250.f, 0)

	, m_CaughtEnemy(false)
	, m_ThrowTime(1.f)
	, m_FloatTime(3.f)
	, m_FloatRate()
	, m_ThrowRate()
	, m_Direction(direction)

	, m_pCollider(nullptr)
{
}

void BubbleComponent::Initialize()
{
	m_pCollider = GetGameObject()->GetComponent<ColliderComponent>();

	if (m_pCollider->GetIsTrigger())
	{
		auto callback = std::bind(&BubbleComponent::HandleInTrigger,
			this, std::placeholders::_1, std::placeholders::_2);

		m_pCollider->SetTriggerCallback(callback);
	}
}

void BubbleComponent::Update(float dt)
{
	sf::Vector2f offset{};

	m_ThrowRate += dt;

	if (m_ThrowRate >= m_ThrowTime || m_CaughtEnemy)
	{
		m_Velocity.y = -50.f;
		m_Velocity.x = 0;

		m_FloatRate += dt;

		if (m_FloatRate >= m_FloatTime)
		{
			GetGameObject()->Delete();
		}
	}

	offset.x = (m_Direction * m_Velocity.x) * dt;
	offset.y = m_Velocity.y * dt;

	GetParentTransform()->Move(offset);
}

void BubbleComponent::Render()
{
}

void BubbleComponent::HandleInTrigger(GameObject* first, GameObject* other)
{
	first;

	if (other->GetTag() == "Enemy" && !m_CaughtEnemy)
	{
		auto comp = other->GetComponent<AIController>();
		
		if (comp)
		{
			comp->SetVelocity(sf::Vector2f(0, -50.f));
			comp->SetState(EnemyState::INBUBBLE);
			comp->SetFloatTime(m_FloatTime);

			m_CaughtEnemy = true;
		}
	}
}
