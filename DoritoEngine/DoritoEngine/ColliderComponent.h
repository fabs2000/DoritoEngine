#pragma once
#include "BaseComponent.h"

class SpriteComponent;

class ColliderComponent : public BaseComponent
{

public:
	ColliderComponent(bool usingSprite = false, const sf::Vector2f& colliderSize = sf::Vector2f(10.f,10.f));
	virtual ~ColliderComponent() = default;

	ColliderComponent(const ColliderComponent& other) = delete;
	ColliderComponent(ColliderComponent&& other) noexcept = delete;
	ColliderComponent& operator=(const ColliderComponent& other) = delete;
	ColliderComponent& operator=(ColliderComponent&& other) noexcept = delete;

	//Collision Call
	void CheckCollisions(ColliderComponent* other);

	void SetSize(const sf::Vector2f& size);
	void SetIsTrigger(bool isTrigger) { m_IsTrigger = isTrigger; }
	void SetUsingSprite(bool usingSprite) { m_UseSpriteCollisions = usingSprite; }

	void SetCollisionCallback(std::function<void(const SDL_Rect&, ColliderComponent*)> callback)
	{ if(!m_IsTrigger)m_CollisionCallback = callback; }

	void SetTriggerCallback(std::function<void(GameObject*, GameObject*)> callback)
	{ if(m_IsTrigger)m_TriggerCallback = callback; }

	bool GetIsTrigger() { return m_IsTrigger; }
	const SDL_Rect GetCollider() { return m_Collider; }

protected:
	virtual void Initialize();
	virtual void Update(float dt);
	virtual void Render();

private:
	std::function<void(const SDL_Rect&, ColliderComponent*)> m_CollisionCallback = nullptr;
	std::function<void(GameObject*, GameObject*)> m_TriggerCallback = nullptr;

	sf::RectangleShape m_DebugShape;
	SDL_Rect m_Collider;

	// SFML creates a bounding box around images/text, to use this as my collisions, I need a reference to the 
	// Sprite (if it has one, else it uses predetermined sizes)
	bool m_UseSpriteCollisions;
	SpriteComponent* m_pRefToImage;

	bool m_IsTrigger;

	void SetColliderSettings();
};

