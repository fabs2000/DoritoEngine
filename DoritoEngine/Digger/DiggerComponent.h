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
class EntityControllerComponent;

class DiggerComponent final : public BaseComponent
{
public:
	DiggerComponent();

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
	ColliderComponent* m_pCollider;
	SpriteComponent* m_pSprite;
	EntityControllerComponent* m_pController;

	GameInfo m_GameInfoRef;

	sf::Vector2f m_StartPos;

	float m_FireTimer
		, m_FireRate
		, m_DeathTime;

	DiggerState m_State;

	//Actions
	void InitInput();
	void HandleCollisions();
};