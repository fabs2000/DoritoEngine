#pragma once
#include <list>

class GameObject;
class TransformComponent;

class BaseComponent
{
public:
	BaseComponent();
	virtual ~BaseComponent();

	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) noexcept = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

	GameObject* GetGameObject() const { return m_pGameObject; };
	void SetGameObject(GameObject* pParent) { m_pGameObject = pParent; };

	TransformComponent* GetParentTransform() const;
	TransformComponent* GetTransform() const;

	void RootInitialize();
	void RootUpdate(float);
	void RootRender();

protected:
	virtual void Initialize() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;


private:
	TransformComponent* m_pTransform;
	GameObject* m_pGameObject;
};

