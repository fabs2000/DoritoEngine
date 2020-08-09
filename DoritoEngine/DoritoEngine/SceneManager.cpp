#include "DoritoPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>

SceneManager::SceneManager()
	: m_pScenes(std::vector<Scene*>())
	, m_pActiveScene(nullptr)
	, m_pNewActiveScene(nullptr)
	, m_IsInit(false)
{

}

void SceneManager::Update(float dt)
{
	if (m_pNewActiveScene)
	{
		m_pActiveScene = m_pNewActiveScene;
		m_pNewActiveScene = nullptr;
	}

	if (m_pActiveScene)
	{
		m_pActiveScene->RootUpdate(dt);
		m_pActiveScene->RootCollisionUpdate();
	}
}

void SceneManager::Render()
{
	if (m_pActiveScene != nullptr)
		m_pActiveScene->RootRender();
}

void SceneManager::Destroy()
{
	for (auto& scene : m_pScenes)
	{
		SafeDelete(scene);
	}
}

void SceneManager::CreateScene(Scene* pScene)
{
	const auto it = std::find(m_pScenes.begin(), m_pScenes.end(), pScene);

	if (it == m_pScenes.end())
	{
		m_pScenes.push_back(pScene);

		pScene->RootInit();

		if (m_pActiveScene == nullptr && m_pNewActiveScene == nullptr)
			m_pNewActiveScene = pScene;
	}
}

void SceneManager::SetActiveGameScene(const std::string& sceneName)
{
	const auto it = find_if(m_pScenes.begin(), m_pScenes.end(), [sceneName](Scene* scene)
		{
			return strcmp(scene->GetName().c_str(), sceneName.c_str()) == 0;
		});

	if (it != m_pScenes.end())
	{
		m_pNewActiveScene = *it;
	}
}

Scene* SceneManager::GetScene(const std::string& sceneName)
{
	const auto it = find_if(m_pScenes.begin(), m_pScenes.end(), [sceneName](Scene* scene)
		{
			return strcmp(scene->GetName().c_str(), sceneName.c_str()) == 0;
		});

	if (it != m_pScenes.end())
	{
		return *it;
	}

	return nullptr;
}
