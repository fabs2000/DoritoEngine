#include "DoritoPCH.h"
#include "EnemyComponent.h"

#include "ColliderComponent.h"
#include "GameObject.h"
#include "Scene.h"

#include "MathHelpers.h"

EnemyComponent::EnemyComponent()
	: m_Velocity(1.f,0.f)
	, m_pCollider(nullptr)
	, m_MovementAcceleration(5.f)
{
}

void EnemyComponent::Initialize()
{
	m_Velocity *= m_MovementAcceleration;
}

void EnemyComponent::Update(float dt)
{
	HandleMovement(dt);
}

void EnemyComponent::Render()
{}

void EnemyComponent::HandleMovement(float dt)
{
	sf::Vector2f offset{};

	offset = m_Velocity * dt;

	GetParentTransform()->Move(offset);

	std::cout << "Position Enemy: " << GetParentTransform()->GetPosition().x << ", " <<
		GetParentTransform()->GetPosition().y << "\n";
}

void EnemyComponent::HandleCollisions()
{

}
