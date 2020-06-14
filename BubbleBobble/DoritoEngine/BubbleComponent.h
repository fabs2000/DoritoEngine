#pragma once
#include "BaseComponent.h"
#include "InputManager.h"

class ColliderComponent;

class BubbleComponent : public BaseComponent
{
public:
	explicit BubbleComponent(float direction);

	BubbleComponent(const BubbleComponent&) = delete;
	BubbleComponent(BubbleComponent&&) = delete;
	BubbleComponent& operator= (const BubbleComponent&) = delete;
	BubbleComponent& operator= (const BubbleComponent&&) = delete;

protected:
	void Initialize() override;
	void Update(float dt) override;
	void Render() override;

private:
	ColliderComponent* m_pCollider;

	sf::Vector2f m_Velocity;

	bool m_CaughtEnemy;

	float m_ThrowTime
		, m_FloatTime
		, m_ThrowRate
		, m_FloatRate
		, m_Direction;

	void HandleInTrigger(GameObject*, GameObject*);
};

