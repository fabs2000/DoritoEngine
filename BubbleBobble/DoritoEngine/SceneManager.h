#pragma once
#include "Singleton.h"
#include <vector>

	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		~SceneManager();
		
		void CreateScene(Scene* pScene);

		void Update(float dt);
		void Render();

	private:

		friend class Singleton<SceneManager>;

		SceneManager();

		std::vector<Scene*> m_pScenes;
		//Scene* m_pActiveScene;
	};