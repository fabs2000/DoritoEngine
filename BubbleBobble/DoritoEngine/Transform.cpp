#include "DoritoPCH.h"
#include "Transform.h"
#include "MathHelpers.h"

#include "GameObject.h"
#include "ColliderComponent.h"

TransformComponent::TransformComponent()
	: m_BaseTransform()
	, m_Origin()
	, m_Position()
	, m_Rotation()
	, m_Scale()
	, m_IsChanged(false)
{
}

void TransformComponent::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;

	m_BaseTransform.setPosition(m_Position);
}

void TransformComponent::SetPosition(sf::Vector2f& pos)
{
	SetPosition(pos.x, pos.y);
}

void TransformComponent::Move(float offX, float offY)
{
	m_Position += sf::Vector2f(offX, offY);

	m_BaseTransform.move(offX, offY);
}

void TransformComponent::Move(sf::Vector2f& offset)
{
	Move(offset.x, offset.y);
}

void TransformComponent::SetRotation(float angle, bool isRadian)
{
	float totRot = angle;

	if (isRadian)
		totRot = DoritoMath::RadiansToDegrees(angle);

	m_Rotation = totRot;
	m_BaseTransform.setRotation(totRot);
}

void TransformComponent::Rotate(float angleOff, bool isRadian)
{
	float totRot = angleOff;

	if (isRadian)
		totRot = DoritoMath::RadiansToDegrees(angleOff);

	m_BaseTransform.rotate(totRot);
}

void TransformComponent::SetScale(float x, float y)
{
	//m_IsChanged = true;

	m_Scale.x = x;
	m_Scale.y = y;

	m_BaseTransform.setScale(m_Scale);
}

void TransformComponent::SetScale(sf::Vector2f& scale)
{
	SetScale(scale.x, scale.y);
}

void TransformComponent::Scale(float factorX, float factorY)
{
	//m_IsChanged = true;

	m_BaseTransform.scale(factorX, factorY);
}

void TransformComponent::Scale(sf::Vector2f& factor)
{
	Scale(factor.x, factor.y);
}

void TransformComponent::SetOrigin(float x, float y)
{
	m_Origin.x = x;
	m_Origin.y = y;

	m_BaseTransform.setOrigin(m_Origin);
}

void TransformComponent::SetOrigin(sf::Vector2f& pos)
{
	SetOrigin(pos.x, pos.y);
}

