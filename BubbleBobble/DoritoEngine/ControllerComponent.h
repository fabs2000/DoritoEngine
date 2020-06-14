#pragma once
#include "BaseComponent.h"
#include "InputManager.h"

enum class PlayerStates
{
	MOVING,
	JUMPING,
	GROUNDED,
	FALLING
};

class ColliderComponent;

class ControllerComponent final : public BaseComponent
{
public:
	explicit ControllerComponent(PlayerControllers playerID = PlayerControllers::Player1);

	ControllerComponent(const ControllerComponent&) = delete;
	ControllerComponent(ControllerComponent&&) = delete;
	ControllerComponent& operator= (const ControllerComponent&) = delete;
	ControllerComponent& operator= (const ControllerComponent&&) = delete;

protected:
	void Initialize() override;
	void Update(float dt) override;
	void Render() override;

private:
	PlayerControllers m_PlayerID;

	sf::Vector2f m_Velocity;
	sf::Vector2f m_Gravity;

	float m_MoveDirection
		, m_JumpForce
		, m_MovementAcceleration;

	PlayerStates m_PlayerState;

	//Actions
	void MoveRight();
	void MoveLeft();

	void ShootBubbles();
	void Jump();

	void InitInput();
	void HandleMovement(float dt);

	ColliderComponent* m_pCollider;

	void HandleCollisions(const SDL_Rect&);
	void Teleport();
};

