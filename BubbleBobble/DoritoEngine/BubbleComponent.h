#pragma once
#include "BaseComponent.h"
#include "InputManager.h"

class ColliderComponent;

class BubbleComponent : public BaseComponent
{
public:
	explicit BubbleComponent();

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

	float m_ThrowTime
		, m_FloatTime
		, m_ThrowRate
		, m_FloatRate;

	void HandleInTrigger();
};

