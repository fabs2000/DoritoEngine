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

		auto pSprite = new SpriteComponent(fileName, true);
		pPlayer->AddComponent(pSprite);

		auto pDigger = new DiggerComponent(player);
		pPlayer->AddComponent(pDigger);

		auto pCollider = new ColliderComponent(true);
		pPlayer->AddComponent(pCollider);

		pPlayer->SetTag("Digger");

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

		auto pController = new EnemyComponent();
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

	inline GameObject* MakeShot(Scene* pScene, const std::string& fileName, const sf::Vector2f& direction)
	{
		auto pShot = new GameObject(pScene);

		auto pLifeTime = new LifeTimeComponent(4.f);
		pShot->AddComponent(pLifeTime);

		auto pComp = new SpriteComponent(fileName);
		pShot->AddComponent(pComp);

		auto pCollider = new ColliderComponent(true);
		pCollider->SetIsTrigger(true);
		pShot->AddComponent(pCollider);

		auto pBubcomp = new FireBallComponent(direction);
		pShot->AddComponent(pBubcomp);

		pShot->GetTransform()->SetScale(2.5f,2.5f);

		pShot->SetTag("Shot");

		return pShot;
	}

	inline GameObject* MakeDirtBlock(Scene* pScene, )
	{

	}
}