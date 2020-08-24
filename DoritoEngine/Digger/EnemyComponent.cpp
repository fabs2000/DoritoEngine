#include "DoritoPCH.h"
#include "EnemyComponent.h"

#include "ColliderComponent.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "Renderer.h"
#include "GoldComponent.h"
#include "DiggerComponent.h"

#include "MathHelpers.h"


EnemyComponent::EnemyComponent(const sf::Vector2f& startPos)
	: m_Velocity(0.f, 0.f)
	, m_pCollider(nullptr)
	, m_pTrigger(nullptr)
	, m_pSceneRef(nullptr)
	, m_pSprite(nullptr)
	, m_Type(EnemyType::NOBBIN)
	, m_Direction(0.f, 0.f)
	, m_StartPos(startPos)
	, m_MovementAcceleration(130.f)
	, m_DetectionRange(500.f)
	, m_TimeForHobbin(15.f)
	, m_Casts(std::array<SDL_Rect, 4>())
	, m_ControlledByPlayer(false)
	, m_FollowingPlayer(false)
{
}

void EnemyComponent::Initialize()
{
	m_pSceneRef = GetGameObject()->GetScene();
	m_pSprite = GetGameObject()->GetComponent<SpriteComponent>();
	auto colliders = GetGameObject()->GetComponents<ColliderComponent>();

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


	m_pCollider = GetGameObject()->GetComponent<ColliderComponent>();

	if (m_pCollider->GetIsTrigger())
	{

	}

	SDL_Rect up;
	up.x = 0; up.y = 0;
	up.w = 5; up.h = -70;

	SDL_Rect down;
	down.x = 0; down.y = 0;
	down.w = 5; down.h = 70;

	SDL_Rect right;
	right.x = 0; right.y = 0;
	right.w = 70; right.h = 5;

	SDL_Rect left;
	left.x = 0; left.y = 0;
	left.w = -70; left.h = 5;

	m_Casts.at(0) = up;
	m_Casts.at(1) = down;
	m_Casts.at(2) = right;
	m_Casts.at(3) = left;
}

void EnemyComponent::Update(float dt)
{
	if (!m_ControlledByPlayer)
	{
		if (m_TimeForHobbin > 0.f)
			m_TimeForHobbin -= dt;

		if (m_TimeForHobbin <= 0.f && m_Type != EnemyType::HOBBIN)
		{
			m_Type = EnemyType::HOBBIN;
			m_MovementAcceleration = 120.f;
			m_DetectionRange = 700.f;
			GetGameObject()->SetTag("Hobbin");
			m_pSprite->SetTexture("hobbin.png");
		}

		HandleDirToPlayer();

		float angleToPlayer = DoritoMath::RadiansToDegrees(atan2f(m_Direction.x, m_Direction.y));

		//DOWN
		if (angleToPlayer < 45.f && angleToPlayer > -45.f)
			m_Direction = sf::Vector2f(0, 1);
		//RIGHT
		else if (angleToPlayer > 45.f && angleToPlayer < 135.f)
			m_Direction = sf::Vector2f(1, 0);
		//UP
		else if (angleToPlayer > 135.f && angleToPlayer < -135.f)
			m_Direction = sf::Vector2f(0, -1);
		//LEFT
		else if (angleToPlayer > -135.f && angleToPlayer < -45.f)
			m_Direction = sf::Vector2f(-1, 0);

		HandleMovement(dt);
	}
}

void EnemyComponent::Render()
{
	if (Renderer::GetInstance()->GetDebugRendering())
	{
		sf::CircleShape range;
		range.setRadius(m_DetectionRange);
		range.setOrigin(GetParentTransform()->GetOrigin());
		range.setPosition(GetParentTransform()->GetPosition());
		range.setPointCount(60);
		range.setFillColor(sf::Color(0, 0, 0, 127));
		range.setOutlineThickness(1.f);
		range.setOutlineColor(sf::Color(255, 0, 0, 127));

		Renderer::GetInstance()->RenderShape(range);
	}
}

void EnemyComponent::HandleMovement(float dt)
{
	auto offset = sf::Vector2f();

	m_Velocity = m_Direction * m_MovementAcceleration;

	offset = m_Velocity * dt;

	GetParentTransform()->Move(offset);

	//std::cout << "Position Enemy: " << GetParentTransform()->GetPosition().x << ", " <<
	//	GetParentTransform()->GetPosition().y << "\n";
}

void EnemyComponent::HandleDirToPlayer()
{
	auto enemyPos = GetParentTransform()->GetPosition();
	auto diggerPos = m_pSceneRef->GetObjectWithTag("Digger")->GetTransform()->GetPosition();

	float distance = DoritoMath::Distance(enemyPos, diggerPos);

	if (distance < m_DetectionRange)
		m_FollowingPlayer = true;
	else
		m_FollowingPlayer = false;

	if (m_FollowingPlayer)
	{
		auto directionToPlayer = diggerPos - GetParentTransform()->GetPosition();

		if (std::fabs(directionToPlayer.x) > std::fabs(directionToPlayer.y)
			|| DoritoMath::FEquals(directionToPlayer.x, directionToPlayer.y))
		{
			if (std::signbit(directionToPlayer.x))
				m_Direction = sf::Vector2f(-1.f, 0.f);
			else
				m_Direction = sf::Vector2f(1.f, 0.f);
		}
		else
		{
			if (std::signbit(directionToPlayer.y))
				m_Direction = sf::Vector2f(0.f, -1.f);
			else
				m_Direction = sf::Vector2f(0.f, 1.f);
		}
	}


	if (enemyPos.x > 1600.f || enemyPos.x < 0.f  || enemyPos.y > 900.f || enemyPos.y < 102.f)
		GetParentTransform()->SetPosition(m_StartPos);
	//if (m_Type == EnemyType::NOBBIN)
		//{
		//	m_pDirt = m_pSceneRef->GetStaticColliders();
		//	//Update raycast Pos
		//	for (auto& box : m_Casts)
		//	{
		//		box.x = static_cast<int>(GetParentTransform()->GetPosition().x);
		//		box.y = static_cast<int>(GetParentTransform()->GetPosition().y);
		//	}
		//	//For all Raycasts compare to all colliders 
		//	for (auto& staticColl : m_pDirt)
		//	{
		//		for (auto& direction : m_Casts)
		//		{
		//			SDL_Rect other = staticColl->GetCollider();
		//			auto enemyPos = GetParentTransform()->GetPosition();
		//			if (enemyPos.x == 0.f && enemyPos.y == 0.f)
		//				continue;
		//
		//			float distance = DoritoMath::Distance(enemyPos,
		//				sf::Vector2f(static_cast<float>(other.x), static_cast<float>(other.y)));
		//			if (distance < m_DetectionRange)
		//			{
		//				if (!SDL_HasIntersection(&direction, &other))
		//				{
		//					m_Direction = DoritoMath::Normalize(directionToPlayer);
		//				}
		//			}
		//		}
		//	}
		//}
		//else
		//{
		//	if (std::fabs(directionToPlayer.x) > std::fabs(directionToPlayer.y)
		//		|| DoritoMath::FEquals(directionToPlayer.x, directionToPlayer.y))
		//	{
		//		if (std::signbit(directionToPlayer.x))
		//			m_Direction = sf::Vector2f(-1.f, 0.f);
		//		else
		//			m_Direction = sf::Vector2f(1.f, 0.f);
		//	}
		//	else
		//	{
		//		if (std::signbit(directionToPlayer.y))
		//			m_Direction = sf::Vector2f(0.f, -1.f);
		//		else
		//			m_Direction = sf::Vector2f(0.f, 1.f);
		//	}
		//}
}

void EnemyComponent::HandleCollisions()
{
	auto triggerCallback = [this](GameObject* first, GameObject* other)
	{
		if (other->GetTag() == "Digger")
		{
			auto digger = other->GetComponent<DiggerComponent>();
			auto sprite = other->GetComponent<SpriteComponent>();

			if (digger->GetState() == DiggerState::MOVING)
			{
				digger->SetState(DiggerState::DEAD);

				first->GetScene()->GetSubject()->Notify(3);
				sprite->SetTexture("grave.png");
			}
		}
	};

	m_pTrigger->SetTriggerCallback(triggerCallback);

	auto collisionCallback = [this](const SDL_Rect& inter, GameObject* first, GameObject* other)
	{
		if (m_Type == EnemyType::NOBBIN)
		{
			if (other->GetTag() == "Dirt" || other->GetTag() == "Limit")
			{
				auto firstPos = first->GetTransform()->GetPosition();
				auto vector = firstPos - other->GetTransform()->GetPosition();
				float angle = DoritoMath::RadiansToDegrees(std::atan2f(vector.x, vector.y));

				if (angle > 60.f && angle < 120.f)
				{
					first->GetTransform()->SetPosition(firstPos.x + static_cast<float>(inter.w), firstPos.y);

					m_Direction = sf::Vector2f(0.f, -1.f);
				}
				else if (angle < -60.f && angle > -120.f)
				{
					first->GetTransform()->SetPosition(firstPos.x - static_cast<float>(inter.w), firstPos.y + static_cast<float>(inter.h));

					m_Direction = sf::Vector2f(0.f, 1.f);
				}
				else if (angle < 60.f && angle > -60.f)
				{
					first->GetTransform()->SetPosition(firstPos.x, firstPos.y + static_cast<float>(inter.h));

					m_Direction = sf::Vector2f(1.f, 0.f);
				}
				else if (angle > 120.f && angle > -120.f)
				{
					first->GetTransform()->SetPosition(firstPos.x, firstPos.y - static_cast<float>(inter.h));

					m_Direction = sf::Vector2f(-1.f, 0.f);
				}
			}
		}
	};

	m_pCollider->SetCollisionCallback(collisionCallback);
}
