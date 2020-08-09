#pragma once
#include "GameObject.h"
#include "Components.h"
#include "InputManager.h"

#include "PracticalHelpers.h"

//---------------------------------------\\
//⁣ 🔻🔺🔻🔺🔻🔺🔻🔻🔻🔻🔺🔺🔻🔺🔺  \\
// 🔻🔻🔺🔻🔻🔺🔻🔺🔻🔺🔻🔺🔻🔺🔺   \\
// 🔻🔻🔺🔻🔺🔻🔺🔻🔺🔻🔻🔺🔻🔺🔻    \\
// 🔻🔺🔻🔺🔻🔺⁣🔻🔺🔺🔺🔻🔺🔻🔻🔺    //
// 🔺🔺🔻🔺🔺🔺🔻🔺🔻🔺🔻🔺🔻🔻🔺   //
// Dammit I spilled my Doritos 😑         //
//---------------------------------------//

namespace DoritoFactory
{
	inline GameObject* MakeCharacter(Scene* pScene, const std::string& fileName, PlayerControllers player)
	{
		GameObject* pPlayer = new GameObject(pScene);
		auto pSprite = new SpriteComponent(fileName, false);
		pPlayer->AddComponent(pSprite);

		auto pController = new ControllerComponent(player);
		pPlayer->AddComponent(pController);

		auto pCollider = new ColliderComponent(true);
		pPlayer->AddComponent(pCollider);

		pPlayer->SetTag("Player");

		return pPlayer;
	}

	inline GameObject* MakeTextObject(Scene* pScene, const std::string& text, const std::string& fileName, unsigned int size)
	{
		GameObject* textObj = new GameObject(pScene);

		auto pText = new TextComponent(text, fileName, size);
		textObj->AddComponent(pText);

		return textObj;
	}

	inline GameObject* MakeLevel(Scene* pScene, const std::string& spriteFile, const std::string& jsonFile)
	{
		GameObject* level = new GameObject(pScene);

		//Level Visualization
		auto pSprite = new SpriteComponent(spriteFile);
		level->AddComponent(pSprite);

		//Make level Colliders
		auto colliders = DoritoHelpers::ReadJson(jsonFile);

		for (auto& collider : colliders["Level"])
		{
			auto pCollider = new ColliderComponent(false, sf::Vector2f(collider["Width"], collider["Height"]));
			level->AddComponent(pCollider);
			pCollider->GetTransform()->SetPosition(collider["X"], collider["Y"]);
		}

		level->SetTag("Level");

		return level;
	}

	inline GameObject* MakeCollider(Scene* pScene, const sf::Vector2f& size)
	{
		GameObject* ground = new GameObject(pScene);
		auto pCollider = new ColliderComponent(false, sf::Vector2f(size.x, size.y));
		ground->AddComponent(pCollider);
		
		return ground;
	}

	inline GameObject* MakeEnemy(Scene* pScene, const std::string& fileName)
	{
		GameObject* pEnemy = new GameObject(pScene);
		auto pSprite = new SpriteComponent(fileName, false);
		pEnemy->AddComponent(pSprite);

		auto pController = new AIController();
		pEnemy->AddComponent(pController);

		auto pCollider = new ColliderComponent(true);
		pEnemy->AddComponent(pCollider);

		pEnemy->SetTag("Enemy");

		return pEnemy;
	}

	inline GameObject* MakeSprite(Scene* pScene, const std::string& fileName)
	{
		auto pSprite = new GameObject(pScene);

		auto pComp = new SpriteComponent(fileName);
		pSprite->AddComponent(pComp);

		return pSprite;
	}

	inline GameObject* MakeBubble(Scene* pScene, const std::string& fileName, float direction)
	{
		auto pBubble = new GameObject(pScene);

		auto pComp = new SpriteComponent(fileName);
		pBubble->AddComponent(pComp);

		auto pCollider = new ColliderComponent(true);
		pCollider->SetIsTrigger(true);
		pBubble->AddComponent(pCollider);

		auto pBubcomp = new BubbleComponent(direction);
		pBubble->AddComponent(pBubcomp);

		pBubble->GetTransform()->SetScale(2.5f,2.5f);

		pBubble->SetTag("Bubble");

		return pBubble;
	}
}