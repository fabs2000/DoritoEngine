#pragma once
#include "Transform.h"

#include <string>
#include <memory>
#include <vector>

class BaseComponent;
class Scene;

class GameObject final
{
public:
	GameObject();
	virtual ~GameObject();

	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	void RootInit();
	void RootUpdate(float dt);
	void RootRender() const;

	TransformComponent* GetTransform() const { return m_pTransform; };

	Scene* GetScene() const { return m_pScene; };
	void SetScene(Scene* pScene) { m_pScene = pScene; };

	void AddComponent(BaseComponent* pComp);
	void RemoveComponent(BaseComponent* pComp);

	//Templated Getters
#pragma region

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
	T* GetComponents()
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

protected:
	virtual void Initialize() {};
	virtual void Update(float) {};
	virtual void Render() const {};

private:
	TransformComponent* m_pTransform;
	std::vector<BaseComponent*> m_pComponents;

	Scene* m_pScene;
};