#include "DoritoPCH.h"
#include "EnemyComponent.h"

#include "ColliderComponent.h"
#include "GameObject.h"
#include "Scene.h"

#include "MathHelpers.h"

EnemyComponent::EnemyComponent()
	: m_Velocity(0.f,0.f)
	, m_pCollider(nullptr)
	, m_MovementAcceleration()
{
}

void EnemyComponent::Initialize()
{

}

void EnemyComponent::Update(float dt)
{
	dt;
}

void EnemyComponent::Render()
{

}

void EnemyComponent::HandleMovement(float)
{
}

void EnemyComponent::HandleCollisions()
{

}
