#include "DoritoPCH.h"
#include "Components.h"

#include "GameObject.h"
#include "Scene.h"
#include "Renderer.h"

ColliderComponent::ColliderComponent(bool usingSprite, const sf::Vector2f& colliderSize)
	: m_Shape()
	, m_Collider{ 0, 0, static_cast<int>(colliderSize.x), static_cast<int>(colliderSize.y) }
	, m_UseSpriteCollisions(usingSprite)
	, m_pRefToImage(nullptr)
	, m_IsTrigger(false)
{
}

void ColliderComponent::CheckCollisions(std::list<ColliderComponent*>& other)
{
	if (!other.empty())
	{
		for (auto& otherPhysComp : other)
		{
			if (otherPhysComp != this)
			{
				SDL_Rect intersect;

				if (SDL_IntersectRect( &m_Collider, &otherPhysComp->m_Collider, &intersect))
				{
					if (m_IsTrigger)
					{
						if (m_TriggerCallback)
						{
							m_TriggerCallback(this->GetGameObject(), otherPhysComp->GetGameObject());
						}
					}
					else
					{
						if (m_CollisionCallback)
						{
							m_CollisionCallback(intersect, otherPhysComp);
						}
					}
				}
			}
		}
	}
	else
	{
		std::cout << "No Physics Components in Scene\n";
	}
}

void ColliderComponent::SetSize(const sf::Vector2f& size)
{
	m_Shape.setSize(size);

	m_Collider.w = static_cast<int>(size.x);
	m_Collider.h = static_cast<int>(size.y);
}

void ColliderComponent::Initialize()
{
	//Debug Drawing
	m_Shape.setFillColor(sf::Color(0, 0, 0, 127));
	m_Shape.setOutlineThickness(1.f);
	m_Shape.setOutlineColor(sf::Color(255, 255, 0, 127));

	m_Shape.setOrigin(GetTransform()->GetOrigin());
	m_Shape.setSize(sf::Vector2f(static_cast<float>(m_Collider.w), static_cast<float>(m_Collider.h)));

	if (m_UseSpriteCollisions) 
		m_pRefToImage = GetGameObject()->GetComponent<SpriteComponent>();

	SetColliderSettings();
}

void ColliderComponent::Update(float)
{
	//Needs to be called here in order to update dimensions in casef of a transformation
	//Could be better with a boolean as to not set these every frame
	//TODO: BOOLEAN
	SetColliderSettings();
}

void ColliderComponent::Render()
{
	Renderer::GetInstance()->RenderShape(m_Shape);
}

void ColliderComponent::SetColliderSettings()
{
	if (m_pRefToImage)
	{
		auto coll = sf::IntRect(m_pRefToImage->GetBounds());
		
		m_Collider = {coll.left, coll.top, coll.width, coll.height};

		m_Shape.setPosition(sf::Vector2f(static_cast<float>(m_Collider.x), static_cast<float>(m_Collider.y)));
		m_Shape.setSize(sf::Vector2f(static_cast<float>(m_Collider.w), static_cast<float>(m_Collider.h)));
	}
	else
	{
		auto& pos = GetTransform()->GetPosition();

		m_Collider.x = static_cast<int>(pos.x);
		m_Collider.y = static_cast<int>(pos.y);

		m_Shape.setPosition(pos);
	}
}
