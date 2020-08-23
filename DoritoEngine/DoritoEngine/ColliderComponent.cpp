#include "DoritoPCH.h"
#include "ColliderComponent.h"
#include "SpriteComponent.h"

#include "GameObject.h"
#include "Scene.h"
#include "Renderer.h"

#include "Cell.h"

ColliderComponent::ColliderComponent(ColliderType type, bool usingSprite, const sf::Vector2f& colliderSize, CollisionGrid* pGrid)
	: m_pParentGrid(pGrid)
	, m_Type(type)
	, m_DebugShape()
	, m_Collider{ 0, 0, static_cast<int>(colliderSize.x), static_cast<int>(colliderSize.y) }
	, m_UseSpriteCollisions(usingSprite)
	, m_pRefToImage(nullptr)
	, m_IsTrigger(false)
{
	//if(m_Type == ColliderType::STATIC)
	//	m_pParentGrid->AddCollider(this);
}

void ColliderComponent::CheckCollisions(ColliderComponent* otherPhysComp)
{
	if (otherPhysComp != this && otherPhysComp != nullptr)
	{
		GameObject* first = this->GetGameObject()
			,* other = otherPhysComp->GetGameObject();

		if (first != other)
		{
			SDL_Rect intersect;

			if (SDL_IntersectRect(&m_Collider, &otherPhysComp->m_Collider, &intersect))
			{
				if (m_IsTrigger)
				{
					if (m_TriggerCallback)
					{
  						m_TriggerCallback(first, other);
					}
				}
				else
				{
					if (m_CollisionCallback)
					{
  						m_CollisionCallback(intersect, first, other);
					}
				}
			}
		}
	}
}

void ColliderComponent::SetSize(const sf::Vector2f& size)
{
	m_DebugShape.setSize(size);

	m_Collider.w = static_cast<int>(size.x);
	m_Collider.h = static_cast<int>(size.y);
}

void ColliderComponent::Initialize()
{
	//Debug Drawing
	m_DebugShape.setFillColor(sf::Color(0, 0, 0, 127));
	m_DebugShape.setOutlineThickness(1.f);
	m_DebugShape.setOutlineColor(sf::Color(255, 255, 0, 127));

	m_DebugShape.setOrigin(GetTransform()->GetOrigin());
	m_DebugShape.setSize(sf::Vector2f(static_cast<float>(m_Collider.w), static_cast<float>(m_Collider.h)));

	if (m_UseSpriteCollisions)
		m_pRefToImage = GetGameObject()->GetComponent<SpriteComponent>();

	SetColliderSettings();
}

void ColliderComponent::Update(float)
{
	//Needs to be called here in order to update dimensions in case of a transformation
	//Could be better with a boolean as to not set these every frame
	SetColliderSettings();
}

void ColliderComponent::Render()
{
	Renderer::GetInstance()->RenderShape(m_DebugShape);
}

void ColliderComponent::SetColliderSettings()
{
	if (m_pRefToImage)
	{
		auto coll = sf::IntRect(m_pRefToImage->GetBounds());

		m_Collider = { coll.left, coll.top, coll.width, coll.height };

		if (Renderer::GetInstance()->GetDebugRendering())
		{
			m_DebugShape.setPosition(sf::Vector2f(static_cast<float>(m_Collider.x), static_cast<float>(m_Collider.y)));
			m_DebugShape.setSize(sf::Vector2f(static_cast<float>(m_Collider.w), static_cast<float>(m_Collider.h)));
		}
	}
	else
	{
		auto& pos = GetTransform()->GetPosition();

		m_Collider.x = static_cast<int>(pos.x);
		m_Collider.y = static_cast<int>(pos.y);

		if (Renderer::GetInstance()->GetDebugRendering())
			m_DebugShape.setPosition(pos);
	}
}
