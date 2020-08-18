#pragma once
#include "BaseComponent.h"

enum class ColliderType
{
	STATIC = 0,
	DYNAMIC = 1
};

class SpriteComponent;
class CollisionGrid;

class ColliderComponent : public BaseComponent
{

public:
	typedef std::function<void(const SDL_Rect&, ColliderComponent*)> CollisionCallback;
	typedef std::function<void(GameObject*, GameObject*)> TriggerCallback;
	
	ColliderComponent(CollisionGrid* pGrid, ColliderType type, bool usingSprite = false, const sf::Vector2f& colliderSize = sf::Vector2f(10.f, 10.f));

	//Collision Call
	void CheckCollisions(ColliderComponent* other);

	void SetSize(const sf::Vector2f& size);
	void SetIsTrigger(bool isTrigger) { m_IsTrigger = isTrigger; }
	void SetUsingSprite(bool usingSprite) { m_UseSpriteCollisions = usingSprite; }

	void SetCollisionCallback(CollisionCallback callback)
	{
		if (!m_IsTrigger)m_CollisionCallback = callback;
	}
	void SetTriggerCallback(TriggerCallback callback)
	{
		if (m_IsTrigger)m_TriggerCallback = callback;
	}

	bool GetIsTrigger() { return m_IsTrigger; }
	const SDL_Rect GetCollider() { return m_Collider; }
	ColliderType GetType() { return m_Type; }

protected:
	virtual void Initialize();
	virtual void Update(float dt);
	virtual void Render();

private:
	CollisionGrid* m_pParentGrid;
	ColliderType m_Type;
	

	CollisionCallback m_CollisionCallback = nullptr;
	TriggerCallback m_TriggerCallback = nullptr;

	sf::RectangleShape m_DebugShape;
	SDL_Rect m_Collider;
	bool m_IsTrigger;

	// SFML creates a bounding box around images/text, to use this as my collisions, 
	// I need a reference to the Sprite (if it has one, else it uses predetermined sizes)
	bool m_UseSpriteCollisions;
	SpriteComponent* m_pRefToImage;

	void SetColliderSettings();
};

