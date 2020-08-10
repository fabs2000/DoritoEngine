#pragma once
#include "DoritoPCH.h"
#include "BaseComponent.h"

enum class EnemyState
{
	DEFAULT,
	INBUBBLE
};

class ColliderComponent;

class AIController : public BaseComponent
{
public:
	explicit AIController();

	AIController(const AIController&) = delete;
	AIController(AIController&&) = delete;
	AIController& operator= (const AIController&) = delete;
	AIController& operator= (const AIController&&) = delete;

	void SetState(EnemyState state) { m_EnemyState = state; }
	void SetVelocity(const sf::Vector2f& vel) { m_Velocity = vel; }
	void SetFloatTime(float time) { m_FloatTime = time; };

protected:
	void Initialize() override;
	void Update(float dt) override;
	void Render() override;

private:
	EnemyState m_EnemyState;

	sf::Vector2f m_Velocity;
	sf::Vector2f m_Gravity;

	float m_MovementAcceleration
		, m_FloatTime
		, m_FloatRate
		, m_OriginalVelX;
	
	void HandleMovement(float dt);
	void FloatUp(float dt);

	ColliderComponent* m_pCollider;

	void HandleCollisions();
	void Teleport();
};


