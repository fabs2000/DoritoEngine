#include "DoritoPCH.h"
#include "Components.h"

#include "GameObject.h"
#include "Scene.h"
#include "Renderer.h"

ColliderComponent::ColliderComponent(bool usingSprite, const sf::Vector2f& colliderSize)
	: m_DebugShape()
	, m_Collider{ 0, 0, static_cast<int>(colliderSize.x), static_cast<int>(colliderSize.y) }
	, m_UseSpriteCollisions(usingSprite)
	, m_pRefToImage(nullptr)
	, m_IsTrigger(false)
{
}

void ColliderComponent::CheckCollisions(ColliderComponent* otherPhysComp)
{
	if (otherPhysComp != this && otherPhysComp != nullptr)
	{
		SDL_Rect intersect;

		if (SDL_IntersectRect(&m_Collider, &otherPhysComp->m_Collider, &intersect))
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
	m_DebugShape.setOutlineThickness(0.1f);
	m_DebugShape.setOutlineColor(sf::Color(255, 255, 0, 127));

	m_DebugShape.setOrigin(GetTransform()->GetOrigin());
	m_DebugShape.setSize(sf::Vector2f(static_cast<float>(m_Collider.w), static_cast<float>(m_Collider.h)));

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
