#include "DoritoPCH.h"
#include "GameObject.h"
#include "BaseComponent.h"

#include "ResourceManager.h"
#include "Renderer.h"

GameObject::GameObject(Scene* pParentScene)
	: m_pScene(pParentScene)
	, m_pTransform(nullptr)
	, m_Tag( "Default" )
	, m_MarkedForDelete(false)
	, m_IsInit(false)
{
	m_pTransform = new TransformComponent();
}

GameObject::~GameObject()
{
	SafeDelete(m_pTransform);

	for (auto& component : m_pComponents)
	{
		SafeDelete(component);
	}
}

void GameObject::AddComponent(BaseComponent* pComp)
{
	m_pComponents.push_back(pComp);
	pComp->SetGameObject(this);
}

void GameObject::RemoveComponent(BaseComponent* pComp)
{
	auto it = find(m_pComponents.begin(), m_pComponents.end(), pComp);

#if _DEBUG
	if (it == m_pComponents.end())
	{
		std::cout << "GameObject::RemoveComponent > Component is not attached to this GameObject!\n";
		return;
	}
#endif

	m_pComponents.erase(it);
	pComp->SetGameObject(nullptr);
}

void GameObject::RootInit()
{
	if (!m_IsInit)
	{
		for (auto& component : m_pComponents)
		{
			component->RootInitialize();
		}
		m_IsInit = true;
	}
}

void GameObject::RootUpdate(float dt)
{
	for (auto& component : m_pComponents)
	{
		component->RootUpdate(dt);
	}
}

void GameObject::RootRender() const
{
	for (auto& component : m_pComponents)
	{
		component->RootRender();
	}
}