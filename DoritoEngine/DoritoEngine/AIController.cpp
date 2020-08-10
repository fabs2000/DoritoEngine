#include "DoritoPCH.h"
#include "AIController.h"

#include "ColliderComponent.h"
#include "GameObject.h"
#include "Scene.h"

#include "MathHelpers.h"

AIController::AIController()
	: m_EnemyState(EnemyState::DEFAULT)
	, m_Velocity(static_cast<float>(DoritoMath::Rand(-1, 1)), 0)
	, m_Gravity(0.f, 800.f)
	, m_MovementAcceleration(DoritoMath::RandF(50.f, 100.f))
	, m_FloatTime()
	, m_FloatRate()
	, m_OriginalVelX()
	, m_pCollider(nullptr)
{
}

void AIController::Initialize()
{
	m_pCollider = GetGameObject()->GetComponent<ColliderComponent>();

	if (m_pCollider)
	{
		HandleCollisions();
	}

	if (m_Velocity.x == 0)
		m_Velocity.x = 1.f;

	m_Velocity *= m_MovementAcceleration;
}

void AIController::Update(float dt)
{
	if (m_EnemyState == EnemyState::INBUBBLE)
		FloatUp(dt);
	else
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

	m_OriginalVelX = m_Velocity.x;

	GetParentTransform()->Move(offset);
}

void AIController::FloatUp(float dt)
{
	m_FloatRate += dt;
	
	if (m_FloatRate <= m_FloatTime)
	{
		sf::Vector2f offset{};

		offset = m_Velocity * dt;

		GetParentTransform()->Move(offset);
	}
	else
	{
		m_EnemyState = EnemyState::DEFAULT;

		m_Velocity.x = m_OriginalVelX;
		m_Velocity.y = 0.f;

		m_FloatRate = 0.f;
	}
}

void AIController::HandleCollisions()
{
	auto callback = [this](const SDL_Rect& intersect, ColliderComponent* other)->void
	{
		if (!other->GetIsTrigger())
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

				GetParentTransform()->SetPosition(pos.x + (direction * intersect.w), pos.y);
				GetParentTransform()->SetScale(direction * 0.3f, 0.3f);
				m_Velocity.x = -m_Velocity.x;
			}
		}
	};

	m_pCollider->SetCollisionCallback(callback);
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
