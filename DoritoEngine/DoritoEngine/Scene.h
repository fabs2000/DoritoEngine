#pragma once
#pragma once
#include "SceneManager.h"
#include "DoritoEngine.h"
#include "Observer.h"
#include "Grid.h"
#include <string>
#include <list>
#include <deque>

class GameObject;
class ColliderComponent;

class Scene
{

public:
	explicit Scene(const std::string& name, const GameInfo& gameInfo);

	virtual ~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

	void AddObject(GameObject* object);
	void RemoveObject(GameObject* object);

	GameObject* GetObjectWithTag(const std::string& tag);
	void ClearObjectsWithTag(const std::string& tag);
	void ClearAllObjects();

	const std::string& GetName() const { return m_Name; }
	Subject* GetSubject() const { return m_pSubject; }
	CollisionGrid* GetGrid() const { return m_pGrid; }
	const GameInfo& GetGameInfo() const{ return m_GameInfo; }

	const std::vector<ColliderComponent*>& GetStaticColliders() const
	{ return m_pStaticColliders; };

	void RootInit();
	void RootUpdate(float dt);
	void RootCollisionUpdate();
	void RootRender() const;

protected:
	virtual void Initialize() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() const = 0;

private:
	std::string m_Name;

	std::list<GameObject*> m_pBasicObjects;

	std::vector<ColliderComponent*> m_pDynamicColliders;
	std::vector<ColliderComponent*> m_pStaticColliders;
	
	std::vector<ColliderComponent*> m_pDynamicCollDel;
	std::vector<ColliderComponent*> m_pStaticCollDel;

	std::vector<ColliderComponent*> m_pPhysicsComps;
	std::vector<ColliderComponent*> m_pPhysicsCompsDel;

	Subject* m_pSubject;
	CollisionGrid* m_pGrid;

	GameInfo m_GameInfo;

	bool m_IsInit;
	
	void RemoveDynamicColliders();
	void RemoveStaticColliders();

	void RemoveAllColliders();
};

