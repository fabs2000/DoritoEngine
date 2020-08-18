#pragma once
#include "DoritoPCH.h"
#include "ColliderComponent.h"
#include "Grid.h"

class Cell
{
public:

	Cell() = default;
	~Cell() = default;


	void AddCollider(ColliderComponent* pColl)
	{
		m_pColliders.push_back(pColl);
	}
	const std::vector<ColliderComponent*>& GetColliders() const { return m_pColliders; }


private:
	std::vector<ColliderComponent*> m_pColliders;

	CollisionGrid* m_pParentGrid;
};

