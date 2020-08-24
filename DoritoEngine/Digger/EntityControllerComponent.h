#pragma once
#include "BaseComponent.h"
#include "InputManager.h"
#include "DoritoEngine.h"

class EntityControllerComponent : public BaseComponent
{
public:
	explicit EntityControllerComponent(PlayerControllers playerID = PlayerControllers::Player1, float acceleration = 100.f);

	EntityControllerComponent(const EntityControllerComponent&) = delete;
	EntityControllerComponent(EntityControllerComponent&&) = delete;
	EntityControllerComponent& operator= (const EntityControllerComponent&) = delete;
	EntityControllerComponent& operator= (const EntityControllerComponent&&) = delete;

	void SetCanMove(bool move) { m_CanMove = move; }

protected:
	void Initialize() override;
	void Update(float dt) override;
	void Render() override;

private:
	PlayerControllers m_PlayerID;

	sf::Vector2f m_Velocity;
	float m_MovementAcceleration;

	GameInfo m_GameInfoRef;

	bool m_CanMove;

	//Actions
	void InitInput();
	void HandleMovement(float dt);
};

