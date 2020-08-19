#pragma once
#include "BaseComponent.h"
#include "DoritoEngine.h"

enum class GoldState
{
	IN_BAG = 0,
	OUT_BAG = 1
};

class ColliderComponent;
class SpriteComponent;

class GoldComponent : public BaseComponent
{
public:
	GoldComponent();

	void SetVeloctiy(const sf::Vector2f& vel) { m_Velocity = vel; }
	const sf::Vector2f& GetVelocity() const { return m_Velocity; };

protected:
	void Initialize() override;
	void Update(float) override;
	void Render() override {};

private:
	ColliderComponent* m_pTrigger;
	ColliderComponent* m_pCollider;
	SpriteComponent* m_pSprite;

	sf::Vector2f m_Velocity
		, m_Gravity
		, m_OriginalPos;

	GoldState m_State;

	float m_BreakingSpeed
		, m_BreakingDistance;

	bool m_IsColliding;

	void HandleCollisions();
};

