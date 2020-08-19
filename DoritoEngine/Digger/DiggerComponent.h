#pragma once
#include "BaseComponent.h"
#include "InputManager.h"
#include "DoritoEngine.h"

enum class DiggerState
{
	MOVING = 0,
	STOPPED = 1
};

class ColliderComponent;

class DiggerComponent final : public BaseComponent
{
public:
	explicit DiggerComponent(PlayerControllers playerID = PlayerControllers::Player1);

	DiggerComponent(const DiggerComponent&) = delete;
	DiggerComponent(DiggerComponent&&) = delete;
	DiggerComponent& operator= (const DiggerComponent&) = delete;
	DiggerComponent& operator= (const DiggerComponent&&) = delete;

protected:
	void Initialize() override;
	void Update(float dt) override;
	void Render() override;

private:
	sf::Vector2f m_Velocity;
	float m_MovementAcceleration;

	PlayerControllers m_PlayerID;
	GameInfo m_GameInfoRef;

	ColliderComponent* m_pCollider;

	float m_FireTimer
		, m_FireRate;



	//Actions
	void InitInput();

	void HandleMovement(float dt);
	void HandleCollisions();

};