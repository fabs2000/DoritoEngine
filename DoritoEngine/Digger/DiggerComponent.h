#pragma once
#include "BaseComponent.h"
#include "InputManager.h"
#include "DoritoEngine.h"

enum class PlayerStates
{
	MOVING,
	JUMPING,
	GROUNDED,
	FALLING
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
	PlayerControllers m_PlayerID;

	sf::Vector2f m_Velocity;
	float m_MovementAcceleration;

	PlayerStates m_PlayerState;
	GameInfo m_GameInfoRef;
	ColliderComponent* m_pCollider;

	//Actions
	void InitInput();
	void HandleMovement(float dt);
	void HandleCollisions();


};