#pragma once
#include "SceneManager.h"
#include <string>

class GameObject;

class Scene
{

public:
	explicit Scene(const std::string& name);

	virtual ~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

	void AddObject(GameObject* object);
	void RemoveObject(GameObject* object);

	const std::string& GetName() const { return m_Name; };

	void RootInit();
	void RootUpdate(float dt);
	void RootRender() const;

protected:

	virtual void Initialize() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() const = 0;

private:

	std::string m_Name;
	std::vector<GameObject*> m_pGameObjects{};

	bool m_IsInit;

	static unsigned int m_IdCounter;
};
