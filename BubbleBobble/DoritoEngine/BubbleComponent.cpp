#include "DoritoPCH.h"

#include "BubbleComponent.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "Scene.h"

BubbleComponent::BubbleComponent()
	: m_Velocity(200.f, 0)

	, m_ThrowTime(1.f)
	, m_FloatTime(1.f)
	, m_FloatRate()
	, m_ThrowRate()

	, m_pCollider(nullptr)
{
}

void BubbleComponent::Initialize()
{
	m_pCollider = GetGameObject()->GetComponent<ColliderComponent>();

	if (m_pCollider->GetIsTrigger())
	{
		auto callback = std::bind(&BubbleComponent::HandleInTrigger,
			this/*, std::placeholders::_1*/);

		m_pCollider->SetTriggerCallback(callback);
	}
}

void BubbleComponent::Update(float dt)
{
	sf::Vector2f offset{};

	m_ThrowRate += dt;

	if (m_ThrowRate >= m_ThrowTime)
	{
		m_Velocity.y = -200.f;
		m_Velocity.x = 0;

		m_FloatRate += dt;

		if (m_FloatRate >= m_FloatTime)
		{
			GetGameObject()->Delete();
		}
	}

	offset = m_Velocity * dt;

	GetParentTransform()->Move(offset);
}

void BubbleComponent::Render()
{
}

void BubbleComponent::HandleInTrigger()
{
	std::cout << "In trigger thing\n";
}
