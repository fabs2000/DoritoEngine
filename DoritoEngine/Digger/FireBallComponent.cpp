#include "DoritoPCH.h"

#include "FireBallComponent.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "Scene.h"
#include "AIController.h"

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
		auto callback = std::bind(&FireBallComponent::HandleInTrigger,
			this, std::placeholders::_1, std::placeholders::_2);

		m_pCollider->SetTriggerCallback(callback);
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

void FireBallComponent::HandleInTrigger(GameObject* , GameObject* other)
{
	if (other->GetTag() == "Enemy")
	{
		//auto comp = other->GetComponent<AIController>();
		//
		//if (comp)
		//{
		//	comp->SetVelocity(sf::Vector2f(0, -50.f));
		//	comp->SetState(EnemyState::INBUBBLE);
		//	comp->SetFloatTime(m_FloatTime);
		//	m_CaughtEnemy = true;
		//}
	}
}
