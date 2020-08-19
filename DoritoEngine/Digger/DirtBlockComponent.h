#pragma once
#include "BaseComponent.h"

class ColliderComponent;

class DirtBlockComponent : public BaseComponent
{
public:
	DirtBlockComponent();

protected:
	void Initialize() override;
	void Update(float) override {};
	void Render() override {};

private:
	ColliderComponent* m_pCollider;

	void HandleInTrigger();
};

