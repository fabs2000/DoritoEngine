#include "DoritoPCH.h"
#include "EnemyComponent.h"

#include "ColliderComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "Renderer.h"

#include "MathHelpers.h"


EnemyComponent::EnemyComponent()
	: m_Velocity(0.f, 0.f)
	, m_pCollider(nullptr)
	, m_pSceneRef(nullptr)
	, m_Type(EnemyType::NOBBIN)
	//, m_Direction(MovementDirection::LEFT)
	, m_Direction(0.f,0.f)
	, m_MovementAcceleration(120.f)
	, m_DetectionRange(80.f)
	, m_TimeForHobbin(15.f)
	//, m_Casts(std::map<MovementDirection, SDL_Rect>())
{
}

void EnemyComponent::Initialize()
{
	m_pSceneRef = GetGameObject()->GetScene();

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

	//m_Casts =
	//{
	//	{MovementDirection::UP, up},
	//	{MovementDirection::DOWN, down},
	//	{MovementDirection::RIGHT, right},
	//	{MovementDirection::LEFT, left}
	//};

	m_Casts.at(0) = up;
	m_Casts.at(1) = down;
	m_Casts.at(2) = right;
	m_Casts.at(3) = left;
}

void EnemyComponent::Update(float dt)
{
	HandleEnemyType();

	//switch (m_Direction)
	//{
	//case MovementDirection::UP:
	//	std::cout << "UP\n";
	//	m_Velocity.y = -m_MovementAcceleration;
	//	m_Velocity.x = 0;
	//	break;
	//case MovementDirection::DOWN:
	//	std::cout << "DOWN\n";
	//	m_Velocity.y = m_MovementAcceleration;
	//	m_Velocity.x = 0;
	//	break;
	//case MovementDirection::LEFT:
	//	std::cout << "LEFT\n";
	//	m_Velocity.x = -m_MovementAcceleration;
	//	m_Velocity.y = 0;
	//	break;
	//case MovementDirection::RIGHT:
	//	std::cout << "RIGHT\n";
	//	m_Velocity.x = m_MovementAcceleration;
	//	m_Velocity.y = 0;
	//	break;
	//}

	float angleToPlayer = DoritoMath::RadiansToDegrees(atan2f(m_Direction.x, m_Direction.y));

	std::cout << angleToPlayer << "\n";

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
		m_Direction = sf::Vector2f(-1,0);

	HandleMovement(dt);
}

void EnemyComponent::Render()
{
	if (Renderer::GetInstance()->GetDebugRendering())
	{
		for (auto& box : m_Casts)
		{
			sf::RectangleShape debugShape{};

			debugShape.setPosition(sf::Vector2f(static_cast<float>(box.x), static_cast<float>(box.y)));
			debugShape.setSize(sf::Vector2f(static_cast<float>(box.w), static_cast<float>(box.h)));

			debugShape.setFillColor(sf::Color(0, 0, 0, 127));
			debugShape.setOutlineThickness(1.f);
			debugShape.setOutlineColor(sf::Color(255, 0, 0, 127));

			Renderer::GetInstance()->RenderShape(debugShape);
		}
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

void EnemyComponent::HandleEnemyType()
{
	auto diggerPos = m_pSceneRef->GetObjectWithTag("Digger")->GetTransform()->GetPosition();

	auto directionToPlayer = diggerPos - GetParentTransform()->GetPosition();

	if (m_Type == EnemyType::NOBBIN)
	{
		m_pDirt = m_pSceneRef->GetStaticColliders();

		//Update raycast Pos
		for (auto& box : m_Casts)
		{
			box.x = static_cast<int>(GetParentTransform()->GetPosition().x);
			box.y = static_cast<int>(GetParentTransform()->GetPosition().y);
		}

		//For all Raycasts compare to all colliders 
		for (auto& staticColl : m_pDirt)
		{
			for (auto& direction : m_Casts)
			{
				SDL_Rect other = staticColl->GetCollider();

				auto enemyPos = GetParentTransform()->GetPosition();

				if (enemyPos.x == 0.f && enemyPos.y == 0.f)
					continue;

				float distance = DoritoMath::Distance(enemyPos,
					sf::Vector2f(static_cast<float>(other.x), static_cast<float>(other.y)));

				if (distance < m_DetectionRange)
				{
					if (!SDL_HasIntersection(&direction, &other))
					{
						m_Direction = DoritoMath::Normalize(directionToPlayer);
					}
				}
			}
		}
	}
	else
	{
		GetGameObject()->SetTag("Hobbin");

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
}
