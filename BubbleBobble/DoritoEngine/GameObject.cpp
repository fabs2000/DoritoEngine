#include "DoritoPCH.h"
#include "GameObject.h"
#include "BaseComponent.h"

#include "ResourceManager.h"
#include "Renderer.h"

GameObject::GameObject() 
	: m_pTransform(nullptr)
{
	m_pTransform = new TransformComponent();
	AddComponent(m_pTransform);
}

GameObject::~GameObject()
{
	for (auto component : m_pComponents)
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
	Initialize();

	for (auto component : m_pComponents)
	{
		component->RootInitialize();
	}
}

void GameObject::RootUpdate(float dt)
{
	Update(dt);

	for (auto component : m_pComponents)
	{
		component->RootUpdate(dt);
	}
}

void GameObject::RootRender() const
{
	Render();

	for (auto component : m_pComponents)
	{
		component->RootRender();
	}
}