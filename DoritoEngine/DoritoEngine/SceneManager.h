#pragma once
#include "Singleton.h"
#include <vector>
#include <string>
#include <list>

	class Scene;

	class SceneManager
	{
	public:
		static SceneManager* GetInstance()
		{
			static SceneManager instance{};
			return &instance;
		}
		void CreateScene(Scene* pScene);
		void SetActiveGameScene(const std::string& sceneName);

		Scene* GetScene(const std::string& sceneName);
		Scene* GetActiveScene() const { return m_pActiveScene; }

		bool IsActiveScene(const std::string& sceneName);

		void Update(float dt);
		void Render();

		void Destroy();

	private:
		SceneManager();

		std::list<Scene*> m_pScenes;
		Scene* m_pActiveScene;
		Scene* m_pNewActiveScene;

		bool m_IsInit;
	};