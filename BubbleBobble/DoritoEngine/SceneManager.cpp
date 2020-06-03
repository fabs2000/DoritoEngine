#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

SceneManager::~SceneManager()
{
	for (auto scene : m_pScenes)
	{
		delete scene;
		scene = nullptr;
	}
}

void SceneManager::Update(float dt)
{
	for(auto& scene : m_pScenes)
	{
		scene->RootUpdate(dt);
	}
}

void SceneManager::Render()
{
	for (const auto& scene : m_pScenes)
	{
		scene->RootRender();
	}
}

void SceneManager::CreateScene(Scene* pScene)
{
	const auto it = std::find(m_pScenes.begin(), m_pScenes.end(), pScene);

	if (it == m_pScenes.end())
	{
		m_pScenes.push_back(pScene);

		pScene->RootInit();
	}
}
