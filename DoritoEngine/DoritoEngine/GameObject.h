#pragma once
#include "Transform.h"

#include <string>
#include <memory>
#include <vector>
#include <list>

class BaseComponent;
class Scene;

class GameObject final
{
public:
	GameObject(Scene* pParentScene);
	~GameObject();

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	void RootInit();
	void RootUpdate(float dt);
	void RootRender() const;

	TransformComponent* GetTransform() const { return m_pTransform; }

	Scene* GetScene() const { return m_pScene; }
	void SetScene(Scene* pScene) { m_pScene = pScene; }

	void AddComponent(BaseComponent* pComp);
	void AddComponentUpd(BaseComponent* pComp);
	void RemoveComponent(BaseComponent* pComp);

	bool GetMarkedForDelete() { return m_MarkedForDelete; }
	void Delete() { m_MarkedForDelete = true; }

	const std::string& GetTag() { return m_Tag; }
	void SetTag(const std::string& tag) { m_Tag = tag; }

	//Templated Getters
#pragma region Component Searches

	template <class T>
	bool HasComponent(BaseComponent* base)
	{
		base = GetComponent<T>();

		return GetComponent<T>() != nullptr;
	}

	template <class T>
	T* GetComponent()
	{
		const type_info& ti = typeid(T);
		for (auto* component : m_pComponents)
		{
			if (component && typeid(*component) == ti)
				return static_cast<T*>(component);
		}

		return nullptr;
	}

	template <class T>
	std::vector<T*> GetComponents()
	{
		const type_info& ti = typeid(T);
		std::vector<T*> components;

		for (auto* component : m_pComponents)
		{
			if (component && typeid(*component) == ti)
				components.push_back(static_cast<T*>(component));
		}

		return components;
	}

#pragma endregion

private:
	TransformComponent* m_pTransform;

	Scene* m_pScene;
	std::string m_Tag;

	std::list<BaseComponent*> m_pComponents;

	bool m_MarkedForDelete;
	bool m_IsInit;
};