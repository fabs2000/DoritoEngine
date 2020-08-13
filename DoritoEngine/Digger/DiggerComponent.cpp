#include "DoritoPCH.h"
#include "DiggerComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"

#include <functional>

#include "MathHelpers.h"
#include "DoritoFactory.h"
#include "ColliderComponent.h"

DiggerComponent::DiggerComponent(PlayerControllers playerID)
	: m_PlayerID(playerID)
	, m_Velocity(0.f, 0.f)
	, m_MovementAcceleration(200.f)
	, m_PlayerState{ PlayerStates::MOVING }
	, m_pCollider(nullptr)
	, m_GameInfoRef()
{

}


void DiggerComponent::Initialize()
{
	m_GameInfoRef = GetGameObject()->GetScene()->GetGameInfo();

	m_pCollider = GetGameObject()->GetComponent<ColliderComponent>();

	if (m_pCollider)
	{
		//Only handles collisions with enemies
		HandleCollisions();
	}

	InitInput();
}

void DiggerComponent::Update(float dt)
{
	HandleMovement(dt);
}

void DiggerComponent::Render()
{}

void DiggerComponent::InitInput()
{
	auto shoot = [this]()->void
	{
		auto transform = GetParentTransform();

		auto direction = sf::Vector2f(cosf(transform->GetRotationRadians()), sinf(transform->GetRotationRadians()));

		if (std::signbit(transform->GetScale().x))
			direction *= -1.f;

		auto pBubble = DoritoFactory::MakeShot(GetGameObject()->GetScene(), "bubble.png", DoritoMath::Normalize(direction));
		auto pos = transform->GetPosition();

		pBubble->GetTransform()->SetPosition(pos);
		GetGameObject()->GetScene()->AddObject(pBubble);
	};

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
		m_Velocity = scale * m_MovementAcceleration;
		m_Velocity *= 2.f;
		m_Velocity.y *= -1;

		auto transform = GetParentTransform();
		auto charScale = transform->GetScale();

			if (scale.x > 0)
			{
				if(std::signbit(charScale.x))
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
	};

	//Keyboard enabled
	m_GameInfoRef.pInput->AddKeyboardEvent(KeyBoardEvent("Shoot", KeyboardButton::Space, shoot, InputTriggerState::Pressed));

	//Controller enabled
	m_GameInfoRef.pInput->AddGamePadActionEvent(GamePadActionEvent("Shoot", GamepadButtons::B,
		m_PlayerID, shoot, InputTriggerState::Pressed));
	m_GameInfoRef.pInput->AddGamePadAxisEvent(GamePadAxisEvent("Move", GamepadAxis::L_STICK,
		m_PlayerID, move, true));
}

void DiggerComponent::HandleMovement(float dt)
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

	m_Velocity = m_Velocity * dt;

	transform->Move(m_Velocity);
}

void DiggerComponent::HandleCollisions()
{
	auto callback = [this](const SDL_Rect& intersect, ColliderComponent* other)->void
	{
		intersect;

		if (other->GetGameObject()->GetTag() == "Enemy")
		{
			auto pSubject = GetGameObject()->GetScene()->GetSubject();
			pSubject->Notify(3);
		}

		//if (!other->GetIsTrigger())
		//{
		//	auto pos = GetParentTransform()->GetPosition();
		//	if (intersect.h < intersect.w)
		//	{
		//		if (m_Velocity.y > 0)
		//		{
		//			m_Velocity.y = 0;
		//			GetParentTransform()->SetPosition(pos.x, pos.y - intersect.h - 0.01f);
		//			m_PlayerState = PlayerStates::GROUNDED;
		//		}
		//	}
		//	else
		//	{
		//		m_Velocity.x = 0;
		//		GetParentTransform()->SetPosition(pos.x + (-m_MovementAcceleration * intersect.w), pos.y);
		//	}
		//}
	};

	m_pCollider->SetCollisionCallback(callback);
}
