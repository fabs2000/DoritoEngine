#pragma once
#include "BaseComponent.h"
#include <vector>

class ColliderComponent;

class DirtBlockComponent : public BaseComponent
{
public:
	DirtBlockComponent() = default;

	DirtBlockComponent(const DirtBlockComponent&) = delete;
	DirtBlockComponent(DirtBlockComponent&&) = delete;
	DirtBlockComponent& operator= (const DirtBlockComponent&) = delete;
	DirtBlockComponent& operator= (const DirtBlockComponent&&) = delete;

protected:
	void Initialize() override;
	void Update(float) override {};
	void Render() override {};

private:
	ColliderComponent* m_pCollider;

	void HandleInTrigger();
};

