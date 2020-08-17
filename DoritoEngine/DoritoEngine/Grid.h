#pragma once
#include "DoritoPCH.h"
#include "ColliderComponent.h"

class Grid
{
public:

	Grid(uint32_t numberOfCells, uint32_t cellSize)
		: m_NumberOfCells(numberOfCells)
		, m_CellSize(cellSize)
	{
		m_pCells.resize(m_NumberOfCells);

		for (int x = 0; x < m_NumberOfCells; x++)
		{
			for (int y = 0; y < m_NumberOfCells; y++)
			{
				m_pCells[x][y] = nullptr;
			}
		}
	}

private:
	std::vector<std::vector<ColliderComponent*>> m_pCells;

	uint32_t m_NumberOfCells, m_CellSize;
};

