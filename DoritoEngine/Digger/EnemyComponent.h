#pragma once
#include "DoritoPCH.h"
#include "BaseComponent.h"

enum class EnemyType
{
	NOBBIN,
	HOBBIN
};

enum class MovementDirection
{
	UP,
	DOWN, 
	RIGHT,
	LEFT
};

class ColliderComponent;
class SpriteComponent;
class Scene;

class EnemyComponent final : public BaseComponent
{
public:
	explicit EnemyComponent(const sf::Vector2f& startPos);

	EnemyComponent(const EnemyComponent&) = delete;
	EnemyComponent(EnemyComponent&&) = delete;
	EnemyComponent& operator= (const EnemyComponent&) = delete;
	EnemyComponent& operator= (const EnemyComponent&&) = delete;

	void SetControlledByPlayer(bool isControl) { m_ControlledByPlayer = isControl; }

protected:
	void Initialize() override;
	void Update(float dt) override;
	void Render() override;

private:
	sf::Vector2f m_Velocity;
	ColliderComponent* m_pCollider;
	ColliderComponent* m_pTrigger;
	SpriteComponent* m_pSprite;
	Scene* m_pSceneRef;

	EnemyType m_Type;
	sf::Vector2f m_Direction;

	sf::Vector2f m_StartPos;

	std::vector<ColliderComponent*> m_pDirt;

	float m_MovementAcceleration
		, m_DetectionRange
		, m_TimeForHobbin;

	void HandleMovement(float dt);
	void HandleDirToPlayer();

	std::array<SDL_Rect, 4> m_Casts;

	bool m_ControlledByPlayer
		, m_FollowingPlayer;

	void HandleCollisions();
};

