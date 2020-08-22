#include "DoritoPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "ColliderComponent.h"

Scene::Scene(const std::string& name, const GameInfo& gameInfo)
	: m_Name(name)
	, m_pBasicObjects(std::list<GameObject*>())

	, m_pDynamicColliders(std::vector<ColliderComponent*>())
	, m_pStaticColliders(std::vector<ColliderComponent*>())

	, m_pDynamicCollDel(std::vector<ColliderComponent*>())
	, m_pStaticCollDel(std::vector<ColliderComponent*>())

	, m_pSubject(new Subject())
	, m_pGrid(new CollisionGrid())
	, m_GameInfo(gameInfo)
	, m_IsInit(false)
{}

Scene::~Scene()
{
	SafeDelete(m_pSubject);
	SafeDelete(m_pGrid);

	for (auto& pSceneObject : m_pBasicObjects)
	{
		//if (pSceneObject->GetTag() == "Digger")
		//	std::cout << "dig\n";

		SafeDelete(pSceneObject);
	}

	m_pBasicObjects.clear();
	
	m_pDynamicColliders.clear();
	m_pStaticColliders.clear();

	m_pDynamicCollDel.clear();
	m_pStaticCollDel.clear();
}

void Scene::AddObject(GameObject* object)
{
	object->RootInit();

	auto physComp = object->GetComponents<ColliderComponent>();

	for (auto& comp : physComp)
	{
		if (comp != nullptr)
		{
			switch (comp->GetType())
			{
			case ColliderType::DYNAMIC:
				m_pDynamicColliders.push_back(comp);
				break;

			case ColliderType::STATIC:
				m_pStaticColliders.push_back(comp);
				break;
			}
		}
	}

	m_pBasicObjects.push_back(object);
}

void Scene::RemoveObject(GameObject* object)
{
	m_pBasicObjects.remove(object);

	auto physComp = object->GetComponents<ColliderComponent>();

	for (auto& comp : physComp)
	{
		if (comp != nullptr)
		{
			switch (comp->GetType())
			{
			case ColliderType::DYNAMIC:
				m_pDynamicCollDel.push_back(comp);		
				break;

			case ColliderType::STATIC:
				m_pStaticCollDel.push_back(comp);
				break;
			}
		}
	}

	SafeDelete(object);
}

void Scene::ClearObjectsWithTag(const std::string& tag)
{
	for (auto& obj : m_pBasicObjects)
	{
		if(obj->GetTag() == tag)
			obj->Delete();
	}
}

void Scene::ClearAllObjects()
{
	for (auto& obj : m_pBasicObjects)
	{
		obj->Delete();
	}
}

void Scene::RootInit()
{
	Initialize();
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

	RemoveStaticColliders();
	RemoveDynamicColliders();
}

void Scene::RootCollisionUpdate()
{
	//m_pGrid->HandleCollisions();

	for (auto& dynamicColl : m_pDynamicColliders)
	{
		for (auto& otherDynamic : m_pDynamicColliders)
		{
			if (dynamicColl != otherDynamic)
			{
				dynamicColl->CheckCollisions(otherDynamic);
			}
		}

		for (auto& staticColl : m_pStaticColliders)
		{
			dynamicColl->CheckCollisions(staticColl);
		}
	}

	for (auto& staticColl : m_pStaticColliders)
	{
		for (auto& otherDynamic : m_pDynamicColliders)
		{
			staticColl->CheckCollisions(otherDynamic);
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

void Scene::RemoveDynamicColliders()
{
	for (auto it = m_pDynamicCollDel.begin(); it != m_pDynamicCollDel.end(); it++)
	{
		auto pCompItDyn = std::find(m_pDynamicColliders.begin(), m_pDynamicColliders.end(), *it);

		if (pCompItDyn != m_pDynamicColliders.end())
		{
			m_pDynamicColliders.erase(pCompItDyn);
		}
	}

	m_pDynamicCollDel.clear();
	//std::cout << "Dynanmic Colliders: " << m_pDynamicColliders.size() << "\n";
}

void Scene::RemoveStaticColliders()
{
	for (auto it = m_pStaticCollDel.begin(); it != m_pStaticCollDel.end(); it++)
	{
		auto pCompItStat = std::find(m_pStaticColliders.begin(), m_pStaticColliders.end(), *it);

		if (pCompItStat != m_pStaticColliders.end())
		{
			m_pStaticColliders.erase(pCompItStat);
		}
	}

	m_pStaticCollDel.clear();

	//std::cout << "Static Colliders: " << m_pStaticColliders.size() << "\n";
}
