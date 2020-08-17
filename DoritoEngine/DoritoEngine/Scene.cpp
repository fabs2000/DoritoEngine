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

	for (auto& comp : physComp)
	{
		if (comp != nullptr)
			m_pPhysicsComponents.push_back(comp);
	}

	m_pBasicObjects.push_back(object);
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
	//for (auto& physComp : m_pPhysicsComponents)
	//{
	//	for (auto& otherComp : m_pPhysicsComponents)
	//	{
	//		if (physComp != otherComp)
	//		{
	//			//auto pos1 = physComp->GetParentTransform()->GetPosition();
	//			//auto pos2 = otherComp->GetParentTransform()->GetPosition();
	//			//if (DoritoMath::SquareDistance(pos1, pos2) < DoritoMath::Square(5.f))
	//			physComp->CheckCollisions(otherComp);
	//		}
	//	}
	//}

	uint32_t maxThreads = std::thread::hardware_concurrency();
	std::deque<std::future<void>> futures;
	uint32_t threadCounter = 0;

	for (auto& physComp : m_pPhysicsComponents)
	{
		if (threadCounter >= maxThreads)
		{
			futures.front().get();
			futures.pop_front();
			threadCounter--;
		}

		futures.emplace_back(std::async(std::launch::async, [&]()
			{
				for (auto& otherComp : m_pPhysicsComponents)
				{
					if (physComp != otherComp)
					{
						//auto pos1 = physComp->GetParentTransform()->GetPosition();
						//auto pos2 = otherComp->GetParentTransform()->GetPosition();
						//if (DoritoMath::SquareDistance(pos1, pos2) < DoritoMath::Square(5.f))

						physComp->CheckCollisions(otherComp);
					}
				}
			}));

		threadCounter++;
	}

	for (auto& future : futures)
	{
		future.get();
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

	std::cout << "Physics: " << m_pPhysicsComponents.size() << "\n";
}
