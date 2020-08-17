#include "DoritoPCH.h"
#include "ChunkCenterComponent.h"

#include "ColliderComponent.h"
#include "GameObject.h"
#include "Scene.h"

#include "MathHelpers.h"

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

		if (other->GetTag() == "Digger")
		{
			first->Delete();

			switch (m_ChunkType)
			{
			case ChunkType::EMERALD:
				first->GetScene()->GetSubject()->Notify(0);
				break;

			case ChunkType::GOLD:
				//Add Gold Bag to scene
				break;

			case ChunkType::DIRT:
				//Does nothing
				break;
			}
		}
	};

	m_pCollider->SetTriggerCallback(callback);
}
