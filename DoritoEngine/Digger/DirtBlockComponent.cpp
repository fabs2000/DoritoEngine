#include "DoritoPCH.h"
#include "DirtBlockComponent.h"

#include "ColliderComponent.h"
#include "GameObject.h"
#include "Scene.h"

#include "MathHelpers.h"

DirtBlockComponent::DirtBlockComponent()
	: m_pCollider(nullptr)
{}

void DirtBlockComponent::Initialize()
{
	m_pCollider = GetGameObject()->GetComponent<ColliderComponent>();

	if (m_pCollider->GetIsTrigger())
	{
		HandleInTrigger();
	}
}

void DirtBlockComponent::HandleInTrigger()
{
	auto callback = [this](GameObject* first, GameObject* other)->void
	{
		//std::cout << "CollidesDirt\n";

		if (other->GetTag() == "Digger")
		{
			first->Delete();
		}
	};

	m_pCollider->SetTriggerCallback(callback);
}
