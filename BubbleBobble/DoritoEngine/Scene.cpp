#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) 
	: m_Name(name) 
{

}

Scene::~Scene()
{
	for (auto& pSceneObject : m_pGameObjects)
	{
		delete pSceneObject;
		pSceneObject = nullptr;
	}
}

void Scene::AddObject(GameObject* object)
{
	m_pGameObjects.push_back(object);
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

