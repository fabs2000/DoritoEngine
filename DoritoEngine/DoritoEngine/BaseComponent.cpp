#include "DoritoPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

BaseComponent::BaseComponent()
	: m_pGameObject( nullptr )
	, m_pTransform( nullptr )
{
	m_pTransform = new TransformComponent();
}

BaseComponent::~BaseComponent()
{
	SafeDelete(m_pTransform);
}

void BaseComponent::RootInitialize()
{
	Initialize();
}
void BaseComponent::RootUpdate(float dt)
{
	Update(dt);
}
void BaseComponent::RootRender()
{
	Render();
}
TransformComponent* BaseComponent::GetParentTransform() const
{
#if _DEBUG
	if (m_pGameObject == nullptr)
	{
		throw std::runtime_error("BaseComponent::GetTransform() > Failed to retrieve the TransformComponent. GameObject is NULL.");
	}
#endif

	return m_pGameObject->GetTransform();
}

TransformComponent* BaseComponent::GetTransform() const
{
	return m_pTransform;
}

