#pragma once
#include "GameObject.h"
#include "Components.h"
#include "InputManager.h"

#include "PracticalHelpers.h"

//---------------------------------------\\
//⁣ 🔻🔺🔻🔺🔻🔺🔻🔻🔻🔻🔺🔺🔻🔺🔺   \\
// 🔻🔻🔺🔻🔻🔺🔻🔺🔻🔺🔻🔺🔻🔺🔺    \\
// 🔻🔻🔺🔻🔺🔻🔺🔻🔺🔻🔻🔺🔻🔺🔻     \\
// 🔻🔺🔻🔺🔻🔺⁣🔻🔺🔺🔺🔻🔺🔻🔻🔺     //
// 🔺🔺🔻🔺🔺🔺🔻🔺🔻🔺🔻🔺🔻🔻🔺    //
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

		auto pCollider = new ColliderComponent(ColliderType::DYNAMIC, true);
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

	inline GameObject* MakeCollider(Scene* pScene, const sf::Vector2f& size)
	{
		GameObject* ground = new GameObject(pScene);

		auto pCollider = new ColliderComponent(ColliderType::STATIC, false, sf::Vector2f(size.x, size.y));
		ground->AddComponent(pCollider);
		
		return ground;
	}

	inline GameObject* MakeEnemyBase(Scene* pScene, const std::string& fileName)
	{
		GameObject* pEnemy = new GameObject(pScene);
		auto pSprite = new SpriteComponent(fileName, true);
		pEnemy->AddComponent(pSprite);

		auto pController = new EnemyComponent();
		pEnemy->AddComponent(pController);

		//Main Collider
		auto pCollider = new ColliderComponent(ColliderType::DYNAMIC, true);
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

	inline GameObject* MakeFireball(Scene* pScene, const std::string& fileName, const sf::Vector2f& direction)
	{
		auto pShot = new GameObject(pScene);

		auto pLifeTime = new LifeTimeComponent(1.25f);
		pShot->AddComponent(pLifeTime);

		auto pComp = new SpriteComponent(fileName);
		pShot->AddComponent(pComp);

		auto pCollider = new ColliderComponent(ColliderType::DYNAMIC, true);
		pCollider->SetIsTrigger(true);
		pShot->AddComponent(pCollider);

		auto pFirecomp = new FireBallComponent(direction);
		pShot->AddComponent(pFirecomp);

		pShot->GetTransform()->SetScale(2.5f,2.5f);

		pShot->SetTag("Shot");

		return pShot;
	}

	inline GameObject* MakeDirtBlock(Scene* pScene, const std::string& file)
	{
		GameObject* pDirtBlock = new GameObject(pScene);

		auto pComp = new SpriteComponent(file);
		pDirtBlock->AddComponent(pComp);

		auto pCollider = new ColliderComponent(ColliderType::STATIC, true);
		pCollider->SetIsTrigger(true);
		pDirtBlock->AddComponent(pCollider);

		auto pCenter = new DirtBlockComponent();
		pDirtBlock->AddComponent(pCenter);

		pDirtBlock->SetTag("Dirt");

		return pDirtBlock;
	}

	inline GameObject* MakeChunkCenter(Scene* pScene, const std::string& file, ChunkType type)
	{
		GameObject* pChunkCenter = new GameObject(pScene);

		auto pComp = new SpriteComponent(file);
		pChunkCenter->AddComponent(pComp);

		auto pCollider = new ColliderComponent(ColliderType::STATIC, true);
		pCollider->SetIsTrigger(true);
		pChunkCenter->AddComponent(pCollider);

		auto pDirt = new ChunkCenterComponent(type);
		pChunkCenter->AddComponent(pDirt);

		pChunkCenter->SetTag("Dirt");

		return pChunkCenter;
	}

	inline GameObject* MakeGoldBag(Scene* pScene, const std::string& file)
	{
		auto pGold = new GameObject(pScene);

		auto pSprite = new SpriteComponent(file);
		pGold->AddComponent(pSprite);

		auto pGoldComp = new GoldComponent();
		pGold->AddComponent(pGoldComp);

		auto pCollider = new ColliderComponent(ColliderType::DYNAMIC, true);
		pGold->AddComponent(pCollider);

		auto pTrigger = new ColliderComponent(ColliderType::DYNAMIC, true);
		pTrigger->SetIsTrigger(true);
		pGold->AddComponent(pTrigger);

		pGold->SetTag("Gold");

		return pGold;
	}

	inline void MakeHUD(Scene* pScene)
	{
		auto pHUD = new GameObject(pScene);

		auto pText = new TextComponent("Score: ", "Lingua.otf", 50);
		pHUD->AddComponent(pText);

		auto pHUDComp = new HUDComponent();
		pHUD->AddComponent(pHUDComp);

		pHUD->SetTag("HUD");

		pScene->AddObject(pHUD);
	}

	inline void MakeEnemy(Scene* pScene, const std::string& fileName, const sf::Vector2f& pos)
	{
		//Enemy has 4 colliders
		// ^ Up
		// > Right 
		// < Left
		// Down

		auto pBaseEnemy = MakeEnemyBase(pScene,fileName);
		pBaseEnemy->GetTransform()->SetPosition(pos);
		pBaseEnemy->GetTransform()->SetScale(0.2f,0.2f);
		pScene->AddObject(pBaseEnemy);

		auto enemyPos = pBaseEnemy->GetTransform()->GetPosition();
		auto enemyBounds = pBaseEnemy->GetComponent<ColliderComponent>()->GetCollider();

		//Right facing
		auto pWallDetector = new ColliderComponent(ColliderType::STATIC, false, sf::Vector2f(static_cast<float>(enemyBounds.w / 2), 1.f));
		pWallDetector->GetTransform()->SetPosition(enemyPos.x + static_cast<float>(enemyBounds.w / 2), enemyPos.y);
		pBaseEnemy->AddComponent(pWallDetector);

		//Left facing
		pWallDetector = new ColliderComponent(ColliderType::STATIC, false, sf::Vector2f(-static_cast<float>(enemyBounds.w / 2), 1.f));
		pWallDetector->GetTransform()->SetPosition(enemyPos.x - static_cast<float>(enemyBounds.w / 2), enemyPos.y);
		pBaseEnemy->AddComponent(pWallDetector);

		//Up facing
		pWallDetector = new ColliderComponent(ColliderType::STATIC, false, sf::Vector2f(1.f, static_cast<float>(enemyBounds.h / 2)));
		pWallDetector->GetTransform()->SetPosition(enemyPos.x, enemyPos.y + static_cast<float>(enemyBounds.h / 2));
		pBaseEnemy->AddComponent(pWallDetector);

		//Down facing
		pWallDetector = new ColliderComponent(ColliderType::STATIC, false, sf::Vector2f(1.f, -static_cast<float>(enemyBounds.h / 2)));
		pWallDetector->GetTransform()->SetPosition(enemyPos.x , enemyPos.y - static_cast<float>(enemyBounds.h / 2));
		pBaseEnemy->AddComponent(pWallDetector);
	}

	inline void MakeDirtChunk(Scene* pScene, const sf::Vector2f& center, const std::string& file, ChunkType type)
	{
		//Dirt chunk holds 9 blocks
		// - 4 Corners of dirt, 2 hori blocks, 2 vert. blocks
		// - 1 center which defines what type of pickup it up
		auto generalScale = sf::Vector2f(0.2f, 0.2f);
		float offset = 1.f;

		//-- Create center --//
		GameObject* pCenter = MakeChunkCenter(pScene, file, type);
		pCenter->GetTransform()->SetPosition(center);
		pCenter->GetTransform()->SetScale(generalScale);
		pScene->AddObject(pCenter);
		

		auto relativeCenter = pCenter->GetTransform()->GetPosition();
		auto centerBounds = pCenter->GetComponent<ColliderComponent>()->GetCollider();

		//-- Create corners --//
		std::vector<GameObject*> pCorners;
		for (UINT i{}; i < 4; i++)
		{
			auto pCorner = MakeDirtBlock(pScene, "Digger/dirt_corner.png");
			
			pCorners.push_back(pCorner);
			pCorner->GetTransform()->SetScale(generalScale);

			pScene->AddObject(pCorner);
		}

		auto cornerBounds = pCorners[0]->GetComponent<ColliderComponent>()->GetCollider();

		//TL
		pCorners[0]->GetTransform()->SetPosition(relativeCenter.x - centerBounds.w/2 - cornerBounds.w/2 - offset,
			relativeCenter.y - centerBounds.h/2 - cornerBounds.w / 2 - offset);
		//TR
		pCorners[1]->GetTransform()->SetPosition(relativeCenter.x + centerBounds.w / 2 + cornerBounds.w / 2 + offset,
			relativeCenter.y - centerBounds.h/2 - cornerBounds.w / 2 - offset);
		//BR
		pCorners[2]->GetTransform()->SetPosition(relativeCenter.x + centerBounds.w / 2 + cornerBounds.w / 2 + offset,
			relativeCenter.y + centerBounds.h/2 + cornerBounds.w / 2 + offset);
		//BL
		pCorners[3]->GetTransform()->SetPosition(relativeCenter.x - centerBounds.w / 2 - cornerBounds.w / 2 - offset,
			relativeCenter.y + centerBounds.h/2 + cornerBounds.w / 2 + offset);

		//-- Create Horizontals --//
		std::vector<GameObject*> pHorizontals;
		for (UINT i{}; i < 2; i++)
		{
			auto pSide = MakeDirtBlock(pScene, "Digger/dirt_horizontal.png");
			pHorizontals.push_back(pSide);
			pSide->GetTransform()->SetScale(generalScale);
			pScene->AddObject(pSide);
		}
		//Top
		pHorizontals[0]->GetTransform()->SetPosition(relativeCenter.x, relativeCenter.y - centerBounds.h/2 - cornerBounds.h/2 - offset);
		//Bot
		pHorizontals[1]->GetTransform()->SetPosition(relativeCenter.x, relativeCenter.y + centerBounds.h / 2 + cornerBounds.h / 2 + offset);
	
		//-- Create Verticals --//
		std::vector<GameObject*> pVerticals;
		for (UINT i{}; i < 2; i++)
		{
			auto pSide = MakeDirtBlock(pScene, "Digger/dirt_vertical.png");
			pVerticals.push_back(pSide);
			pSide->GetTransform()->SetScale(generalScale);
			pScene->AddObject(pSide);
		}

		//Left
		pVerticals[0]->GetTransform()->SetPosition(relativeCenter.x - centerBounds.w/2 - cornerBounds.w/2 - offset, relativeCenter.y);
		//Right
		pVerticals[1]->GetTransform()->SetPosition(relativeCenter.x + centerBounds.w / 2 + cornerBounds.w / 2 + offset, relativeCenter.y);
	}
	
	inline void MakeLevel(Scene* pScene, const std::string& dirtFile)
	{
		//Make level Colliders
		auto chunks = DoritoHelpers::ReadJson(dirtFile);
		for (auto& chunk : chunks["Dirt"])
		{
			auto type = chunk["Type"];

			if (type == ChunkType::NOTHING)
				continue;

			auto pos = sf::Vector2f(chunk["X"], chunk["Y"]);

			MakeDirtChunk(pScene, pos, chunk["Texture"], type);
		}
	}
}