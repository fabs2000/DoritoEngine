#include "DoritoPCH.h"
#include "ControllerComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"

#include <functional>

#include "MathHelpers.h"
#include "DoritoFactory.h"
#include "ColliderComponent.h"

ControllerComponent::ControllerComponent(PlayerControllers playerID)
	: m_PlayerID(playerID)
	, m_Velocity()
	, m_Gravity(0.f, 800.f)
	, m_MoveDirection(1.f)
	, m_PlayerState{ PlayerStates::MOVING }
	, m_JumpForce(500.f)
	, m_MovementAcceleration(200.f)
	, m_pCollider(nullptr)
{
}


void ControllerComponent::Initialize()
{
	m_pCollider = GetGameObject()->GetComponent<ColliderComponent>();

	if (!m_pCollider->GetIsTrigger())
	{
		auto callback = std::bind(&ControllerComponent::HandleCollisions,
			this, std::placeholders::_1, std::placeholders::_2);



		m_pCollider->SetCollisionCallback(callback);
	}

	InitInput();
}

void ControllerComponent::Update(float dt)
{
	HandleMovement(dt);

	Teleport();
}

void ControllerComponent::Render()
{}

void ControllerComponent::InitInput()
{
	auto& gameInfo = GetGameObject()->GetScene()->GetGameInfo();

	auto jump = [this]()->void
	{
		if (m_PlayerState == PlayerStates::GROUNDED)
		{
			m_Velocity.y = -m_JumpForce;
			m_PlayerState = PlayerStates::JUMPING;
		}
	};
	auto shoot = [this]()->void
	{
		auto pBubble = DoritoFactory::MakeBubble(GetGameObject()->GetScene(), "bubble.png", m_MoveDirection);

		auto pos = GetParentTransform()->GetPosition();
		pBubble->GetTransform()->SetPosition(pos.x + (50.f * m_MoveDirection), pos.y - 30.f);

		GetGameObject()->GetScene()->AddObject(pBubble);
	};
	auto left = [this]()->void
	{
		m_Velocity.x = -m_MovementAcceleration;
		GetParentTransform()->SetScale(-0.3f, 0.3f);
		m_MoveDirection = -1.f;
	};
	auto right = [this]()->void
	{
		m_Velocity.x = m_MovementAcceleration;
		GetParentTransform()->SetScale(0.3f, 0.3f);
		m_MoveDirection = 1.f;
	};

	//Keyboard enabled
	gameInfo.pInput->AddKeyboardEvent(KeyBoardEvent("Right", KeyboardButton::D, right));
	gameInfo.pInput->AddKeyboardEvent(KeyBoardEvent("Left", KeyboardButton::A, left));

	gameInfo.pInput->AddKeyboardEvent(KeyBoardEvent("Jump", KeyboardButton::Space, jump, InputTriggerState::Pressed));
	gameInfo.pInput->AddKeyboardEvent(KeyBoardEvent("Shoot", KeyboardButton::LControl, shoot, InputTriggerState::Pressed));

	//Controller enabled
	gameInfo.pInput->AddGamePadEvent(GamePadEvent("Right", GamepadButtons::RIGHT_D, m_PlayerID, right));
	gameInfo.pInput->AddGamePadEvent(GamePadEvent("Left", GamepadButtons::LEFT_D, m_PlayerID, left));

	gameInfo.pInput->AddGamePadEvent(GamePadEvent("Jump", GamepadButtons::A, m_PlayerID, shoot, InputTriggerState::Pressed));
	gameInfo.pInput->AddGamePadEvent(GamePadEvent("Shoot", GamepadButtons::B, m_PlayerID, jump, InputTriggerState::Pressed));
}

void ControllerComponent::HandleMovement(float dt)
{
	sf::Vector2f offset{};

	m_Velocity = m_Velocity + m_Gravity * dt;

	offset = m_Velocity * dt;

	GetParentTransform()->Move(offset);

	m_Velocity.x = 0;
}

void ControllerComponent::HandleCollisions(const SDL_Rect& intersect, ColliderComponent*other)
{
	if (!other->GetIsTrigger())
	{
		auto pos = GetParentTransform()->GetPosition();

		if (intersect.h < intersect.w)
		{
			if (m_Velocity.y > 0)
			{
				m_Velocity.y = 0;
				GetParentTransform()->SetPosition(pos.x, pos.y - intersect.h - 0.01f);
				m_PlayerState = PlayerStates::GROUNDED;
			}
		}
		else
		{
			m_Velocity.x = 0;
			GetParentTransform()->SetPosition(pos.x + (-m_MoveDirection * intersect.w), pos.y);
		}
	}
}

void ControllerComponent::Teleport()
{
	auto& pos = GetGameObject()->GetTransform()->GetPosition();
	auto& gameInfo = GetGameObject()->GetScene()->GetGameInfo();

	if (pos.y > gameInfo.windowSettings.height)
		GetGameObject()->GetTransform()->SetPosition(pos.x, 0);
	else if (pos.y < 0)
		GetGameObject()->GetTransform()->SetPosition(pos.x, static_cast<float>(gameInfo.windowSettings.height));
}
