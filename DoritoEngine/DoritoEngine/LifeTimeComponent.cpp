#include "LifeTimeComponent.h"
#include "GameObject.h"

LifeTimeComponent::LifeTimeComponent(float lifeTime)
	: m_LifeTime(lifeTime)
{
}

void LifeTimeComponent::Update(float dt)
{
	m_LifeTime -= dt;

	if (m_LifeTime < 0)
	{
		GetGameObject()->Delete();
	}

}
