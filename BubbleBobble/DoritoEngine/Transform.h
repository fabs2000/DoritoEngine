#pragma once
#include "BaseComponent.h"

#include "SFML/Graphics/Transform.hpp"


class TransformComponent final
{
public:
	TransformComponent();
	virtual ~TransformComponent() = default;

	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) noexcept = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) noexcept = delete;

	//Positions
	void SetPosition(float x, float y);
	void SetPosition(sf::Vector2f& pos);

	void Move(float offX, float offY);
	void Move(sf::Vector2f& offset);

	//Rotation
	void SetRotation(float angle, bool isRadian = false);
	void Rotate(float angleOff, bool isRadian = false);

	//Scaling
	void SetScale(float x, float y);
	void SetScale(sf::Vector2f& scale);

	void Scale(float factorX, float factorY);
	void Scale(sf::Vector2f& factor);

	void SetOrigin(float x, float y);
	void SetOrigin(sf::Vector2f& pos);

	const sf::Vector2f& GetPosition() const { return m_Position; };
	const sf::Vector2f& GetScale() const { return m_Scale; };
	const sf::Vector2f& GetOrigin() const { return m_Origin; };
	const float GetRotationEuler() const { return m_Rotation; };

	const sf::Transform& GetBaseTransform() const { return m_BaseTransform.getTransform(); };

private:
	sf::Transformable m_BaseTransform;

	sf::Vector2f m_Position, m_Scale, m_Origin;
	float m_Rotation;

	bool m_IsChanged;
};
