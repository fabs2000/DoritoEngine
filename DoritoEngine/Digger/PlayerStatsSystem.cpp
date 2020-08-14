#include "PlayerStatsSystem.h"

PlayerStatsSystem::PlayerStatsSystem()
	: m_TotalScore()
	, m_EmeraldStreak()
	, m_ScoreForLife()
	, m_Lives(1)
	, m_IsGameOver(false)
{
	InitFunctions();
}

void PlayerStatsSystem::OnNotify(uint32_t event)
{
	auto it = m_Actions.find(event);
	 
	if (it != m_Actions.end())
		(*it).second();
	else
		std::cout << "No event bound to message\n";
}

void PlayerStatsSystem::InitFunctions()
{
	auto emeraldCollected = [this]()->void
	{
		AddScore(25);
		m_EmeraldStreak++;
	};

	auto enemyKilled = [this]()->void
	{
		AddScore(250);
	};

	auto goldCollected = [this]()->void
	{
		AddScore(500);
	};

	auto lifeLost = [this]()->void
	{
		m_Lives--;
		if (m_Lives < 0)
			m_IsGameOver = true;
	};

	auto extraLife = [this]()->void
	{
		m_ScoreForLife = 0;
		if (m_Lives < 3)
		m_Lives++;
	};


	m_Actions = std::map<uint32_t, std::function<void()>>{ {0, emeraldCollected}, {1, enemyKilled}, 
		{2, goldCollected}, {3, lifeLost}, {4, extraLife} };
}

void PlayerStatsSystem::Update()
{
	if (m_ScoreForLife >= 20000)
	{
		OnNotify(3);
	}
}

void PlayerStatsSystem::AddScore(unsigned int value)
{
	m_TotalScore += value;
	m_ScoreForLife += value;
}
