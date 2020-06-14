#include "DoritoPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "ColliderComponent.h"

Scene::Scene(const std::string& name, const GameInfo& gameInfo)
	: m_Name(name)
	, m_pBasicObjects()
	, m_pPhysicsComponents()
	, m_GameInfo(gameInfo)
	, m_IsInit(false)
{}

Scene::~Scene()
{
	for (auto& pSceneObject : m_pBasicObjects)
	{
		SafeDelete(pSceneObject);
	}
}

void Scene::AddObject(GameObject* object)
{
	auto physComp = object->GetComponents<ColliderComponent>();

	if (!physComp.empty())
	{
		for (auto& comp : physComp)
		{
			m_pPhysicsComponents.push_back(comp);
		}
	}

	m_pBasicObjects.push_back(object);
}

void Scene::RemoveObject(GameObject* object)
{
	const auto it = find(m_pBasicObjects.begin(), m_pBasicObjects.end(), object);

	if (it != m_pBasicObjects.end())
	{
		m_pBasicObjects.erase(it);
		SafeDelete(object);
	}
}

void Scene::RootInit()
{
	Initialize();

	for (auto& pSceneObj : m_pBasicObjects)
	{
		pSceneObj->RootInit();
	}
}

void Scene::RootUpdate(float dt)
{
	Update(dt);

	for (auto& pSceneObject : m_pBasicObjects)
	{
		pSceneObject->RootUpdate(dt);
	}

	for (auto pObj = m_pBasicObjects.begin(); pObj != m_pBasicObjects.end();)
	{

		(*pObj)->RootUpdate(dt);

		//https://stackoverflow.com/a/16269740
		if ((*pObj)->GetMarkedForDelete())
		{
			auto copy = pObj;
			pObj = ++pObj;
			RemoveObject(*copy);
		}
		else
		{
			++pObj;
		}

	}
}

void Scene::RootCollisionUpdate()
{
	if (!m_pPhysicsComponents.empty())
	{
		for (auto& physComp : m_pPhysicsComponents)
		{
			physComp->CheckCollisions(m_pPhysicsComponents);
		}
	}
}

void Scene::RootRender() const
{
	Render();

	for (const auto& pSceneObject : m_pBasicObjects)
	{
		pSceneObject->RootRender();
	}
}

