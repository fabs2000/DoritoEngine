#include "DoritoPCH.h"
#include "EntityControllerComponent.h"

#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"

#include "MathHelpers.h"

EntityControllerComponent::EntityControllerComponent(PlayerControllers playerID, float acceleration)
	: m_PlayerID(playerID)
	, m_Velocity(0.f, 0.f)
	, m_MovementAcceleration(acceleration)
	, m_GameInfoRef()
	, m_CanMove(true)
{
}

void EntityControllerComponent::Initialize()
{
	m_GameInfoRef = GetGameObject()->GetScene()->GetGameInfo();

	InitInput();
}

void EntityControllerComponent::Update(float dt)
{
	if(m_CanMove)
		HandleMovement(dt);
}

void EntityControllerComponent::Render()
{
}

void EntityControllerComponent::InitInput()
{
	auto left = [this]()->void
	{
		m_Velocity.x = -m_MovementAcceleration;
		GetParentTransform()->SetScale(-0.3f, 0.3f);
		GetParentTransform()->SetRotation(0.f);
	};
	auto right = [this]()->void
	{
		m_Velocity.x = m_MovementAcceleration;
		GetParentTransform()->SetScale(0.3f, 0.3f);
		GetParentTransform()->SetRotation(0.f);
	};
	auto up = [this]()->void
	{
		auto transform = GetParentTransform();
		m_Velocity.y = -m_MovementAcceleration;

		if (std::signbit(transform->GetScale().x))
			transform->SetRotation(90.f);
		else
			transform->SetRotation(270.f);
	};
	auto down = [this]()->void
	{
		auto transform = GetParentTransform();
		m_Velocity.y = m_MovementAcceleration;

		if (std::signbit(transform->GetScale().x))
			transform->SetRotation(270.f);
		else
			transform->SetRotation(90.f);
	};

	auto move = [this](const sf::Vector2f& scale)->void
	{
		auto transform = GetParentTransform();
		if (transform)
		{
			m_Velocity = scale * m_MovementAcceleration;
			m_Velocity.y *= -1;

			auto charScale = transform->GetScale();

			if (scale.x > 0)
			{
				if (std::signbit(charScale.x))
					charScale.x *= -1.f;

				transform->SetScale(charScale);
				transform->SetRotation(0);
			}

			else if (scale.x < 0)
			{
				if (!std::signbit(charScale.x))
					charScale.x *= -1.f;

				transform->SetScale(charScale);
				transform->SetRotation(0);
			}

			sf::Vector2f rot = sf::Vector2f(90.f, -90.f);

			if (std::signbit(transform->GetScale().x))
				rot *= -1.f;

			if (scale.y < 0)
				transform->SetRotation(rot.x);
			else if (scale.y > 0)
				transform->SetRotation(rot.y);

			if (m_PlayerID == PlayerControllers::Player2)
				std::cout << "Player 2 Vel: " << m_Velocity.x << ", " << m_Velocity.y << "\n";
		}
	};

	//m_GameInfoRef.pInput->AddGamePadActionEvent(GamePadActionEvent("Left", GamepadButtons::LEFT_D, m_PlayerID, left, InputTriggerState::Down));
	//m_GameInfoRef.pInput->AddGamePadActionEvent(GamePadActionEvent("Right", GamepadButtons::RIGHT_D, m_PlayerID, right, InputTriggerState::Down));
	//m_GameInfoRef.pInput->AddGamePadActionEvent(GamePadActionEvent("Up", GamepadButtons::UP_D, m_PlayerID, up, InputTriggerState::Down));
	//m_GameInfoRef.pInput->AddGamePadActionEvent(GamePadActionEvent("Down", GamepadButtons::DOWN_D, m_PlayerID, down, InputTriggerState::Down));

	m_GameInfoRef.pInput->AddGamePadAxisEvent(GamePadAxisEvent("Move", GamepadAxis::L_STICK,
		m_PlayerID, move, true));
}

void EntityControllerComponent::HandleMovement(float dt)
{
	auto transform = GetParentTransform();
	auto charScale = transform->GetScale();

	if (m_GameInfoRef.pInput->IsKeyDown(KeyboardButton::Right))
	{
		if (std::signbit(charScale.x))
			charScale.x *= -1.f;

		m_Velocity.x = m_MovementAcceleration;
		transform->SetScale(charScale);
		transform->SetRotation(0.f);
	}
	else if (m_GameInfoRef.pInput->IsKeyDown(KeyboardButton::Left))
	{
		if (!std::signbit(charScale.x))
			charScale.x *= -1.f;

		m_Velocity.x = -m_MovementAcceleration;
		transform->SetScale(charScale);
		transform->SetRotation(0.f);
	}
	else if (m_GameInfoRef.pInput->IsKeyDown(KeyboardButton::Up))
	{
		m_Velocity.y = -m_MovementAcceleration;

		if (std::signbit(transform->GetScale().x))
			transform->SetRotation(90.f);
		else
			transform->SetRotation(270.f);
	}
	else if (m_GameInfoRef.pInput->IsKeyDown(KeyboardButton::Down))
	{
		m_Velocity.y = m_MovementAcceleration;

		if (std::signbit(transform->GetScale().x))
			transform->SetRotation(270.f);
		else
			transform->SetRotation(90.f);
	}

	//if(m_PlayerID == PlayerControllers::Player2)
	//	std::cout << "Player 2 Vel: " << m_Velocity.x << ", " << m_Velocity.y << "\n";

	m_Velocity = m_Velocity * dt;

	transform->Move(m_Velocity);
}
