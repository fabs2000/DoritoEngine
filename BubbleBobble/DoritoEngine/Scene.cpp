#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) 
	: m_Name(name) 
	, m_pGameObjects(std::vector<GameObject*>())
	, m_IsInit(false)
{}

Scene::~Scene()
{
	for (auto& pSceneObject : m_pGameObjects)
	{
		SafeDelete(pSceneObject);
	}
}

void Scene::AddObject(GameObject* object)
{
	object->Initialize();

	m_pGameObjects.push_back(object);
}

void Scene::RemoveObject(GameObject* object)
{
	const auto it = find(m_pGameObjects.begin(), m_pGameObjects.end(), object);

	if (it != m_pGameObjects.end())
	{
		m_pGameObjects.erase(it);

		SafeDelete(object);
	}
}

void Scene::RootInit()
{
	Initialize();

	for (auto& pSceneObj : m_pGameObjects)
	{
		pSceneObj->Initialize();
	}
}

void Scene::RootUpdate(float dt)
{
	Update(dt);

	for(auto& pSceneObject : m_pGameObjects)
	{
		pSceneObject->Update(dt);
	}
}

void Scene::RootRender() const
{
	Render();

	for (const auto& pSceneObject : m_pGameObjects)
	{
		pSceneObject->Render();
	}
}

