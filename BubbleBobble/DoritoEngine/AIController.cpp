#include "DoritoPCH.h"
#include "AIController.h"

#include "ColliderComponent.h"
#include "GameObject.h"
#include "Scene.h"

#include "MathHelpers.h"

AIController::AIController()
	: m_Velocity(static_cast<float>(DoritoMath::Rand(-1, 1)), 0)
	, m_Gravity(0.f, 800.f)
	, m_MovementAcceleration(DoritoMath::RandF(100.f, 200.f))
	, m_pCollider(nullptr)
{
}

void AIController::Initialize()
{
	m_pCollider = GetGameObject()->GetComponent<ColliderComponent>();

	if (m_pCollider)
	{
		auto callback = std::bind(&AIController::HandleCollisions,
			this, std::placeholders::_1);

		m_pCollider->SetCollisionCallback(callback);
	}

	if (m_Velocity.x == 0)
		m_Velocity.x = 1.f;

	m_Velocity *= m_MovementAcceleration;

}

void AIController::Update(float dt)
{
	HandleMovement(dt);

	Teleport();
}

void AIController::Render()
{
}

void AIController::HandleMovement(float dt)
{
	sf::Vector2f offset{};

	m_Velocity = m_Velocity + m_Gravity * dt;

	offset = m_Velocity * dt;

	GetParentTransform()->Move(offset);
}

void AIController::HandleCollisions(const SDL_Rect& intersect)
{
	auto pos = GetParentTransform()->GetPosition();

	if (intersect.h < intersect.w)
	{
		if (m_Velocity.y > 0)
		{
			m_Velocity.y = 0;
			GetParentTransform()->SetPosition(pos.x, pos.y - intersect.h);
		}
	}
	else
	{
		float direction = 0;

		if (m_Velocity.x > 0.f)
		{
			direction = -1.f;
		}
		else
			direction = 1.f;

		GetParentTransform()->SetPosition(pos.x + (direction * 2.f), pos.y);
		GetParentTransform()->SetScale(direction * 0.3f, 0.3f);
		m_Velocity.x = -m_Velocity.x;
	}
}

void AIController::Teleport()
{
	auto& pos = GetGameObject()->GetTransform()->GetPosition();
	auto& gameInfo = GetGameObject()->GetScene()->GetGameInfo();

	if (pos.y > gameInfo.windowSettings.height)
		GetGameObject()->GetTransform()->SetPosition(pos.x, 0);
	else if (pos.y < 0)
		GetGameObject()->GetTransform()->SetPosition(pos.x, static_cast<float>(gameInfo.windowSettings.height));
}
