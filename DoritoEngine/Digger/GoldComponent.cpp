#include "DoritoPCH.h"
#include "GoldComponent.h"

#include "ColliderComponent.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "Scene.h"

#include "DiggerComponent.h"
#include "MathHelpers.h"


GoldComponent::GoldComponent()
	: m_pCollider(nullptr)
	, m_pTrigger(nullptr)
	, m_pSprite(nullptr)
	, m_Velocity()
	, m_Gravity(0.f, 0.f)
	, m_State(GoldState::IN_BAG)
	, m_BreakingSpeed(800.f)
	, m_BreakingDistance(205.f)
	, m_IsColliding(false)
	, m_FallTimer(0.6f)
{
}

void GoldComponent::Initialize()
{
	auto colliders = GetGameObject()->GetComponents<ColliderComponent>();
	m_pSprite = GetGameObject()->GetComponent<SpriteComponent>();

	for (auto& coll : colliders)
	{
		if (coll->GetIsTrigger())
		{
			m_pTrigger = coll;
			continue;
		}

		m_pCollider = coll;
	}

	if ((m_pTrigger && m_pCollider) &&
		(m_pTrigger->GetIsTrigger() && !m_pCollider->GetIsTrigger()))
	{
		HandleCollisions();
	}

	m_OriginalPos = GetParentTransform()->GetPosition();
}

void GoldComponent::Update(float dt)
{
	m_FallTimer -= dt;

	if (m_FallTimer < 0.f)
	{
		if (!m_IsColliding)
			m_Gravity.y = 600.f;
	}

	sf::Vector2f offset{};

	m_Velocity = m_Velocity + m_Gravity * dt;

	offset = m_Velocity * dt;

	GetParentTransform()->Move(offset);

	m_Velocity.x = 0.f;
	m_IsColliding = false;
}

void GoldComponent::HandleCollisions()
{
	auto triggerCallback = [this](GameObject* first, GameObject* other)
	{
		auto otherTag = other->GetTag();

		switch (m_State)
		{
		case GoldState::IN_BAG:
			if (m_Velocity.y > 250.f)
			{
				if (otherTag == "Enemy")
					other->Delete();

				else if (otherTag == "Digger")
				{
					auto digger = other->GetComponent<DiggerComponent>();
					auto sprite = other->GetComponent<SpriteComponent>();

					if (digger->GetState() == DiggerState::MOVING)
					{
						digger->SetState(DiggerState::DEAD);
						first->GetScene()->GetSubject()->Notify(3);
						sprite->SetTexture("Digger/grave.png");
					}
				}
			}
			break;

		case GoldState::OUT_BAG:
			if (otherTag == "Enemy")
			{
				first->Delete();
			}
			else if (otherTag == "Digger")
			{
				first->GetScene()->GetSubject()->Notify(2);
				first->Delete();
			}
			break;
		}
	};

	m_pTrigger->SetTriggerCallback(triggerCallback);

	auto collisionCallback = [this](const SDL_Rect&, GameObject*, GameObject* other)
	{
		if (other->GetTag() == "Dirt")
		{
			m_IsColliding = true;

			if (m_State == GoldState::IN_BAG)
			{
				m_Velocity.y = 0.f;
				m_Gravity.y = 0.f;

				float distance = DoritoMath::Distance
				(m_OriginalPos, GetParentTransform()->GetPosition());

				if (m_BreakingDistance < distance)
				{
					m_State = GoldState::OUT_BAG;

					if (m_pSprite)
						m_pSprite->SetTexture("Digger/goldcoins.png");
				}

				m_OriginalPos = GetParentTransform()->GetPosition();
			}
		}
	};

	m_pCollider->SetCollisionCallback(collisionCallback);
}
