#pragma once
#include "DoritoPCH.h"
#include "ColliderComponent.h"

class Cell;

class CollisionGrid
{
public:

	CollisionGrid();
	~CollisionGrid();

	void HandleCellCollisions(Cell* pCell);
	void HandleCollisions();

	void AddCollider(ColliderComponent* pColl);

	static const uint32_t m_NumberOfCells = 10, m_CellSize = 100;

private:
	Cell* m_pCells[m_NumberOfCells][m_NumberOfCells];
};

