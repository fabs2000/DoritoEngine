#pragma once
#include "BaseComponent.h"

class LifeTimeComponent : public BaseComponent
{
public:
	explicit LifeTimeComponent(float lifeTime);

	LifeTimeComponent(const LifeTimeComponent&) = delete;
	LifeTimeComponent(LifeTimeComponent&&) = delete;
	LifeTimeComponent& operator= (const LifeTimeComponent&) = delete;
	LifeTimeComponent& operator= (const LifeTimeComponent&&) = delete;

protected:
	void Initialize() override {};
	void Update(float dt) override;
	void Render() override {};

private:

	float m_LifeTime;
};

