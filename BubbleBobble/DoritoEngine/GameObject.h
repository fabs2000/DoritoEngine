#pragma once
#include "Transform.h"
#include "Texture2D.h"
#include <string>
#include <memory>

class GameObject
{
public:
	virtual void Initialize();
	virtual void Update(float) {};
	virtual void Render() const;

	void SetTexture(const std::string& filename);
	void SetPosition(float x, float y);

	GameObject() = default;
	virtual ~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

protected:

	Transform m_Transform;
	Texture2D* m_pTexture{};
};