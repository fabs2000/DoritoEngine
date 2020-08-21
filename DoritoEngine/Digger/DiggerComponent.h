#pragma once
#include "BaseComponent.h"
#include "InputManager.h"
#include "DoritoEngine.h"

enum class DiggerState
{
	MOVING = 0,
	DEAD = 1
};

class ColliderComponent;
class SpriteComponent;

class DiggerComponent final : public BaseComponent
{
public:
	explicit DiggerComponent(PlayerControllers playerID = PlayerControllers::Player1);

	DiggerComponent(const DiggerComponent&) = delete;
	DiggerComponent(DiggerComponent&&) = delete;
	DiggerComponent& operator= (const DiggerComponent&) = delete;
	DiggerComponent& operator= (const DiggerComponent&&) = delete;

	DiggerState GetState() { return m_State; }
	void SetState(DiggerState state) { m_State = state; }

protected:
	void Initialize() override;
	void Update(float dt) override;
	void Render() override;

private:
	PlayerControllers m_PlayerID;

	sf::Vector2f m_Velocity;
	float m_MovementAcceleration;

	ColliderComponent* m_pCollider;
	SpriteComponent* m_pSprite;

	GameInfo m_GameInfoRef;

	float m_FireTimer
		, m_FireRate
		, m_DeathTime;

	DiggerState m_State;

	//Actions
	void InitInput();

	void HandleMovement(float dt);
	void HandleCollisions();

};