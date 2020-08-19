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
	, m_pGrid(new CollisionGrid())
{}

Scene::~Scene()
{
	for (auto& pSceneObject : m_pBasicObjects)
	{
		SafeDelete(pSceneObject);
	}

	SafeDelete(m_pSubject);
	SafeDelete(m_pGrid);
}

void Scene::AddObject(GameObject* object)
{
	object->RootInit();

	auto physComp = object->GetComponents<ColliderComponent>();

	for (auto& comp : physComp)
	{
		if (comp != nullptr)
			m_pPhysicsComponents.push_back(comp);
	}

	m_pBasicObjects.push_back(object);
}

void Scene::AddPhysicsObject(ColliderComponent* pColl)
{
	if (pColl != nullptr)
		m_pPhysicsComponents.push_back(pColl);
}

void Scene::RemoveObject(GameObject* object)
{
	m_pBasicObjects.remove(object);

	auto physComp = object->GetComponents<ColliderComponent>();

	//for (auto it = physComp.begin(); it != physComp.end(); it++)
	//{
	//	if (object->GetMarkedForDelete())
	//	{
	//		m_pPhysicsComponents.erase(it);
	//	}
	//	else
	//	{
	//		it++;
	//	}
	//}

	for (auto& comp : physComp)
	{
		m_pPhysCompDel.push_back(comp);
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

	RemovePhysicsComponents();
}

void Scene::RootCollisionUpdate()
{
	//m_pGrid->HandleCollisions();

	for (auto& physComp : m_pPhysicsComponents)
	{
		for (auto& otherComp : m_pPhysicsComponents)
		{
			if (physComp != otherComp)
			{
				if (physComp->GetType() == ColliderType::STATIC 
					&& otherComp->GetType() == ColliderType::STATIC)
				{
					continue;
				}
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

void Scene::RemovePhysicsComponents()
{
	for (auto it = m_pPhysCompDel.begin(); it != m_pPhysCompDel.end(); it++)
	{
		auto pCompIt = std::find(m_pPhysicsComponents.begin(), m_pPhysicsComponents.end(), *it);

		if (pCompIt != m_pPhysicsComponents.end())
		{
			m_pPhysicsComponents.erase(pCompIt);
		}
	}

	//std::cout << "Physics: " << m_pPhysicsComponents.size() << "\n";
}
