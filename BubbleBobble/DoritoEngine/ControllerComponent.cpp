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
			this, std::placeholders::_1);

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

	auto right = std::bind(&ControllerComponent::MoveRight, this);
	auto left = std::bind(&ControllerComponent::MoveLeft, this);

	auto shoot = std::bind(&ControllerComponent::ShootBubbles, this);
	auto jump = std::bind(&ControllerComponent::Jump, this);

	//Keyboard enabled
	gameInfo.pInput->AddKeyboardEvent(KeyBoardEvent("Right", KeyboardButton::D, right));
	gameInfo.pInput->AddKeyboardEvent(KeyBoardEvent("Left", KeyboardButton::A, left));

	gameInfo.pInput->AddKeyboardEvent(KeyBoardEvent("Jump", KeyboardButton::Space, jump, InputTriggerState::Pressed));
	gameInfo.pInput->AddKeyboardEvent(KeyBoardEvent("Shoot", KeyboardButton::LControl, shoot, InputTriggerState::Pressed));

	//Controller enabled
	gameInfo.pInput->AddGamePadEvent(GamePadEvent("Right", GamepadButtons::RIGHT_D, m_PlayerID, right));
	gameInfo.pInput->AddGamePadEvent(GamePadEvent("Left", GamepadButtons::LEFT_D, m_PlayerID, left));

	gameInfo.pInput->AddGamePadEvent(GamePadEvent("Jump", GamepadButtons::A, m_PlayerID, jump, InputTriggerState::Pressed));
	gameInfo.pInput->AddGamePadEvent(GamePadEvent("Shoot", GamepadButtons::B, m_PlayerID, shoot, InputTriggerState::Pressed));
}

void ControllerComponent::HandleMovement(float dt)
{
	sf::Vector2f offset{};

	m_Velocity = m_Velocity + m_Gravity * dt;

	offset = m_Velocity * dt;

	GetParentTransform()->Move(offset);

	m_Velocity.x = 0;
}

void ControllerComponent::HandleCollisions(const SDL_Rect& intersect)
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

void ControllerComponent::Teleport()
{
	auto& pos = GetGameObject()->GetTransform()->GetPosition();
	auto& gameInfo = GetGameObject()->GetScene()->GetGameInfo();

	if (pos.y > gameInfo.windowSettings.height)
		GetGameObject()->GetTransform()->SetPosition(pos.x, 0);
	else if (pos.y < 0)
		GetGameObject()->GetTransform()->SetPosition(pos.x, static_cast<float>(gameInfo.windowSettings.height));
}

void ControllerComponent::ShootBubbles()
{
	auto pBubble = DoritoFactory::MakeBubble(GetGameObject()->GetScene(), "Bob.png");

	auto pos = GetParentTransform()->GetPosition();
	pBubble->GetTransform()->SetPosition(pos.x, pos.y - 30.f);

	GetGameObject()->GetScene()->AddObject(pBubble);
}

void ControllerComponent::Jump()
{
	if (m_PlayerState == PlayerStates::GROUNDED || m_PlayerState != PlayerStates::FALLING)
	{
		m_Velocity.y = -m_JumpForce;
		m_PlayerState = PlayerStates::JUMPING;
	}
}

void ControllerComponent::MoveRight()
{
	m_Velocity.x = m_MovementAcceleration;
	m_MoveDirection = 1.f;
}

void ControllerComponent::MoveLeft()
{
	m_Velocity.x = -m_MovementAcceleration;
	m_MoveDirection = -1.f;
}