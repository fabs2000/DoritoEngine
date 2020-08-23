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
class Scene;

class EnemyComponent final : public BaseComponent
{
public:
	explicit EnemyComponent();

	EnemyComponent(const EnemyComponent&) = delete;
	EnemyComponent(EnemyComponent&&) = delete;
	EnemyComponent& operator= (const EnemyComponent&) = delete;
	EnemyComponent& operator= (const EnemyComponent&&) = delete;

protected:
	void Initialize() override;
	void Update(float dt) override;
	void Render() override;

private:
	sf::Vector2f m_Velocity;
	ColliderComponent* m_pCollider;
	Scene* m_pSceneRef;

	EnemyType m_Type;
	//MovementDirection m_Direction;

	sf::Vector2f m_Direction;

	std::vector<ColliderComponent*> m_pDirt;


	float m_MovementAcceleration
		, m_DetectionRange
		, m_TimeForHobbin;

	void HandleMovement(float dt);
	void HandleEnemyType();

	//std::map<MovementDirection, SDL_Rect> m_Casts;

	std::array<SDL_Rect, 4> m_Casts;
};

