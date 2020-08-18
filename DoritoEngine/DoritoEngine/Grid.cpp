#include "DoritoPCH.h"
#include "Grid.h"

#include "Transform.h"
#include "Cell.h"

CollisionGrid::CollisionGrid()
{
	for (uint32_t x = 0; x < m_NumberOfCells; x++)
	{
		for (uint32_t y = 0; y < m_NumberOfCells; y++)
		{
			m_pCells[x][y] = nullptr;
		}
	}
}

CollisionGrid::~CollisionGrid()
{
	for (auto& cell : m_pCells)
	{
		for (auto& c : cell)
		{
			SafeDelete(c);
		}
	}
}

void CollisionGrid::HandleCellCollisions(Cell* pCell)
{
	for (auto& coll : pCell->GetColliders())
	{
		for (auto& otherColl : pCell->GetColliders())
		{
			if(coll != otherColl)
				coll->CheckCollisions(otherColl);
		}
	}
}

void CollisionGrid::HandleCollisions()
{
	for (uint32_t x{}; x < m_NumberOfCells; x++)
	{
		for (uint32_t y{}; y < m_NumberOfCells; y++)
		{
			HandleCellCollisions(m_pCells[x][y]);
		}
	}
}

void CollisionGrid::AddCollider(ColliderComponent* pColl)
{
	auto pos = pColl->GetParentTransform()->GetPosition();
	
	int cellX = static_cast<int>(pos.x/m_CellSize);
	int cellY = static_cast<int>(pos.y/m_CellSize);

	//push back to cell container
	m_pCells[cellX][cellY]->AddCollider(pColl);
}
