#pragma once
#include "BaseComponent.h"
#include "InputManager.h"

class ColliderComponent;

class FireBallComponent : public BaseComponent
{
public:
	explicit FireBallComponent(const sf::Vector2f& direction);

	FireBallComponent(const FireBallComponent&) = delete;
	FireBallComponent(FireBallComponent&&) = delete;
	FireBallComponent& operator= (const FireBallComponent&) = delete;
	FireBallComponent& operator= (const FireBallComponent&&) = delete;

protected:
	void Initialize() override;
	void Update(float dt) override;
	void Render() override;

private:
	ColliderComponent* m_pCollider;

	sf::Vector2f m_Velocity,
		m_Direction;

	float m_Speed;

	void HandleInTrigger(GameObject*, GameObject*);
};

