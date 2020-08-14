#pragma once
#include "DoritoPCH.h"
#include "BaseComponent.h"

enum class EnemyType
{
	HOBBIN,
	NOBBIN
};

class ColliderComponent;


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

	float m_MovementAcceleration;

	void HandleMovement(float dt);
	void HandleCollisions();
};

