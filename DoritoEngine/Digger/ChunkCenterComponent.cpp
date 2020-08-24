#include "DoritoPCH.h"
#include "ChunkCenterComponent.h"

#include "ColliderComponent.h"
#include "GameObject.h"
#include "Scene.h"

#include <functional>

#include "MathHelpers.h"
#include "DoritoFactory.h"

ChunkCenterComponent::ChunkCenterComponent(ChunkType type)
	: m_pCollider(nullptr)
	, m_ChunkType(type)
{
}

void ChunkCenterComponent::Initialize()
{
	m_pCollider = GetGameObject()->GetComponent<ColliderComponent>();

	if (m_pCollider->GetIsTrigger())
	{
		if (m_ChunkType == ChunkType::GOLD)
		{
			m_pCollider->SetType(ColliderType::DYNAMIC);
		}

		HandleInTrigger();
	}
}

void ChunkCenterComponent::HandleInTrigger()
{
	auto callback = [this](GameObject* first, GameObject* other)->void
	{
		if (first == other)
			return;
		//std::cout << first->GetTransform()->GetPosition().x << ", " << first->GetTransform()->GetPosition().y << "\n";
		if (other->GetTag() == "Digger" || other->GetTag() == "Hobbin")
		{
			GameObject* pGold = nullptr;
			switch (m_ChunkType)
			{
			case ChunkType::EMERALD:
				if (other->GetTag() == "Digger")
				{
					first->GetScene()->GetSubject()->Notify(0);
					first->Delete();
				}
				break;
			case ChunkType::GOLD:
				if (other->GetTag() == "Digger")
				{
					pGold = DoritoFactory::MakeGoldBag(GetGameObject()->GetScene(), "gold.png");
					pGold->GetTransform()->SetScale(0.2f, 0.2f);
					pGold->GetTransform()->SetPosition(GetParentTransform()->GetPosition());
					GetGameObject()->GetScene()->AddObject(pGold);
					first->Delete();
				}
				//std::cout << "Spawned Gold\n";
				break;
			case ChunkType::DIRT:
				//Does nothing
				first->Delete();
				break;
			}
		}
	};


	m_pCollider->SetTriggerCallback(callback);
}

void ChunkCenterComponent::HandleInTrigger(GameObject* first, GameObject* other)
{
	if (first == other)
		return;

	//std::cout << first->GetTransform()->GetPosition().x << ", " << first->GetTransform()->GetPosition().y << "\n";

	if (other->GetTag() == "Digger" || other->GetTag() == "Hobbin")
	{
		GameObject* pGold = nullptr;

		switch (m_ChunkType)
		{
		case ChunkType::EMERALD:
			if (other->GetTag() == "Digger")
			{
				first->GetScene()->GetSubject()->Notify(0);
				first->Delete();
			}
			break;

		case ChunkType::GOLD:
			if (other->GetTag() == "Digger")
			{
				pGold = DoritoFactory::MakeGoldBag(GetGameObject()->GetScene(), "gold.png");
				pGold->GetTransform()->SetScale(0.2f, 0.2f);
				pGold->GetTransform()->SetPosition(GetParentTransform()->GetPosition());
				GetGameObject()->GetScene()->AddObject(pGold);

				first->Delete();
			}

			//std::cout << "Spawned Gold\n";
			break;

		case ChunkType::DIRT:
			//Does nothing
			first->Delete();
			break;
		}
	}
}
