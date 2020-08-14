#pragma once
#include "BaseComponent.h"

enum class DirtType
{
	DIRT = 0,
	EMERALD = 1,
	GOLD = 2
};

class ColliderComponent;

class DirtBlockComponent : public BaseComponent
{
public:
	explicit DirtBlockComponent();

	DirtBlockComponent(const DirtBlockComponent&) = delete;
	DirtBlockComponent(DirtBlockComponent&&) = delete;
	DirtBlockComponent& operator= (const DirtBlockComponent&) = delete;
	DirtBlockComponent& operator= (const DirtBlockComponent&&) = delete;

protected:
	void Initialize() override;
	void Update(float dt) override;
	void Render() override;

private:


};

