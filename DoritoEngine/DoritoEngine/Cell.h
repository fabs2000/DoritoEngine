#pragma once
#include "DoritoPCH.h"
#include "ColliderComponent.h"
#include "Grid.h"

class Cell
{
public:

	//const std::vector<ColliderComponent*>& const GetCollidersInCell()
	//{
	//	return m_pColliders;
	//}

private:
	std::vector<ColliderComponent*> m_pColliders;

	Grid* m_pParentGrid;
};

