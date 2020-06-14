#pragma once
#include "DoritoPCH.h"
#include "BaseComponent.h"


class ColliderComponent;

class AIController : public BaseComponent
{
public:
	explicit AIController();

	AIController(const AIController&) = delete;
	AIController(AIController&&) = delete;
	AIController& operator= (const AIController&) = delete;
	AIController& operator= (const AIController&&) = delete;

protected:
	void Initialize() override;
	void Update(float dt) override;
	void Render() override;

private:
	sf::Vector2f m_Velocity;
	sf::Vector2f m_Gravity;

	float m_MovementAcceleration;
	
	void HandleMovement(float dt);

	ColliderComponent* m_pCollider;

	void HandleCollisions(const SDL_Rect&);
	void Teleport();
};


