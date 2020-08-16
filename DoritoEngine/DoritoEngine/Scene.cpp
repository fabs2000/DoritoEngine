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
	, m_pSubject(new Subject())
{}

Scene::~Scene()
{
	for (auto& pSceneObject : m_pBasicObjects)
	{
		SafeDelete(pSceneObject);
	}

	SafeDelete(m_pSubject);
}

void Scene::AddObject(GameObject* object)
{
	object->RootInit();

	auto physComp = object->GetComponents<ColliderComponent>();

	if (!physComp.empty())
	{
		for (auto& comp : physComp)
		{
			if (comp != nullptr)
				m_pPhysicsComponents.push_back(comp);
		}
	}

	m_pBasicObjects.push_back(object);
}

void Scene::RemoveObject(GameObject* object)
{
	m_pBasicObjects.remove(object);

	auto physComp = object->GetComponents<ColliderComponent>();
	if (!physComp.empty())
	{
		for (auto& comp : physComp)
		{
			m_pPhysicsComponents.remove(comp);
		}
	}
	SafeDelete(object);
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
			for (auto& otherComp : m_pPhysicsComponents)
			{
				if(physComp != otherComp)
					physComp->CheckCollisions(otherComp);
			}
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

