#include "DoritoPCH.h"
#include "EntityControllerComponent.h"
#include "DiggerComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"

#include "MathHelpers.h"
#include "DoritoFactory.h"
#include "ColliderComponent.h"

DiggerComponent::DiggerComponent()
	: m_pCollider(nullptr)
	, m_pSprite(nullptr)
	, m_pController(nullptr)
	, m_GameInfoRef()
	, m_FireTimer(1.f)
	, m_FireRate(0.25f)
	, m_DeathTime(2.f)
	, m_State(DiggerState::MOVING)
{}

void DiggerComponent::Initialize()
{
	m_GameInfoRef = GetGameObject()->GetScene()->GetGameInfo();

	m_pCollider = GetGameObject()->GetComponent<ColliderComponent>();
	m_pSprite = GetGameObject()->GetComponent<SpriteComponent>();
	m_pController = GetGameObject()->GetComponent<EntityControllerComponent>();

	m_StartPos = GetParentTransform()->GetPosition();


	if (m_pCollider)
	{ 
		//Only handles collisions with gold
		HandleCollisions();
	}

	InitInput();
}

void DiggerComponent::Update(float dt)
{
	if (m_FireTimer > 0.f)
		m_FireTimer -= dt;

	switch (m_State)
	{
	case DiggerState::MOVING:
		m_pSprite->SetTexture("digger.png");
		m_pController->SetCanMove(true);
		break;

	case DiggerState::DEAD:
		//Reset position and texture
		m_pController->SetCanMove(false);
		m_DeathTime -= dt;

		if (m_DeathTime <= 0.f)
		{
			GetGameObject()->GetScene()->ClearObjectsWithTag("Nobbin");
			GetGameObject()->GetScene()->ClearObjectsWithTag("Hobbin");

			GetParentTransform()->SetPosition(978, 773);
			m_DeathTime = 2.f;
			m_State = DiggerState::MOVING;
			m_pSprite->SetTexture("digger.png");
		}

		break;
	}
	
	auto pos = GetParentTransform()->GetPosition();

	if (pos.x > 1600.f || pos.x < 0.f || pos.y > 900.f || pos.y < 102.f)
		GetParentTransform()->SetPosition(m_StartPos);
}

void DiggerComponent::Render()
{}

void DiggerComponent::InitInput()
{
	auto shoot = [this]()->void
	{
		if (m_FireTimer >= 0.f)
			return;
		auto go = GetGameObject();
		go;
		auto direction = sf::Vector2f(cosf(GetParentTransform()->GetRotationRadians())
			, sinf(GetParentTransform()->GetRotationRadians()));
		if (std::signbit(GetParentTransform()->GetScale().x))
			direction *= -1.f;
		auto pBubble = DoritoFactory::MakeFireball(GetGameObject()->GetScene(), "fireball.png", DoritoMath::Normalize(direction));
		auto pos = GetParentTransform()->GetPosition();
		pBubble->GetTransform()->SetScale(0.1f, 0.1f);
		pBubble->GetTransform()->SetPosition(pos);
		GetGameObject()->GetScene()->AddObject(pBubble);
		m_FireTimer += 1.0f / m_FireRate;
	};

	//Keyboard enabled
	m_GameInfoRef.pInput->AddKeyboardEvent(KeyBoardEvent("Shoot", KeyboardButton::Space, 
		shoot, InputTriggerState::Pressed));

	//Controller enabled
	m_GameInfoRef.pInput->AddGamePadActionEvent(GamePadActionEvent("Shoot", GamepadButtons::B,
		PlayerControllers::Player1, shoot, InputTriggerState::Pressed));
}

void DiggerComponent::HandleCollisions()
{
	auto callback = [this](const SDL_Rect& inter, GameObject* first, GameObject* other)
	{
		if (other->GetTag() == "Gold")
		{
			auto goldComp = other->GetComponent<GoldComponent>();

			if (goldComp->GetVelocity().y <= 0.f)
			{
				auto firstPos = first->GetTransform()->GetPosition();

				auto vector = firstPos - other->GetTransform()->GetPosition();
				float angle = DoritoMath::RadiansToDegrees(std::atan2f(vector.x, vector.y));

				sf::Vector2f vel;

				if (angle > 60.f && angle < 120.f)
					vel = sf::Vector2f(-400.f, 0.f);
				else if (angle < -60.f && angle > -120.f)
					vel = sf::Vector2f(400.f, 0.f);

				if (angle < 60.f && angle > -60.f)
				{
					first->GetTransform()->SetPosition(firstPos.x, firstPos.y + static_cast<float>(inter.h));
				}
				else if (angle > 120.f && angle > -120.f)
				{
					first->GetTransform()->SetPosition(firstPos.x, firstPos.y - static_cast<float>(inter.h));
				}

				goldComp->SetVeloctiy(vel);
			}
		}
	};

	m_pCollider->SetCollisionCallback(callback);
}
