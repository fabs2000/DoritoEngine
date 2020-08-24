#include "PlayerStatsSystem.h"

#include "Scene.h"

PlayerStatsSystem::PlayerStatsSystem(uint32_t maxEmeralds, uint32_t maxEnemies)
	: m_Lives(3)

	, m_TotalScore()
	, m_ScoreForLife()
	
	, m_EmeraldCount(maxEmeralds)
	, m_EmeraldStreak()

	, m_EnemyCount(maxEnemies)
	, m_MaxEnemies(maxEnemies)
	
	, m_IsGameOver(false)
	, m_LostLife(false)
	, m_GainedLife(false)
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
		m_EmeraldCount--;
		m_EmeraldStreak++;
		AddScore(25);
	};

	auto enemyKilled = [this]()->void
	{
		m_EnemyCount--;
		AddScore(250);
	};

	auto goldCollected = [this]()->void
	{
		std::cout << "Gold Collected\n";
		AddScore(500);
	};

	auto lifeLost = [this]()->void
	{
		m_Lives--;
		m_EmeraldStreak = 0;

		m_LostLife = true;
		m_GainedLife = false;

		std::cout << "Lost Life\n";

		if (m_Lives < 0)
			m_IsGameOver = true;
	};

	auto extraLife = [this]()->void
	{
		if (m_Lives < 3)
		{
			m_ScoreForLife = 0;
			m_GainedLife = true;
			m_LostLife = false;
			m_Lives++;
		}
	};

	auto emeraldStreak = [this]()->void
	{
		m_EmeraldStreak = 0;
		AddScore(250);

		std::cout << "EMERALD STREAK\n";
	};

	auto level1 = [this]()->void
	{
		m_EmeraldCount = 19;
		m_EmeraldStreak = 0;
		m_EnemyCount = 5;

		m_Lives = 3;
		m_TotalScore = 0;
		m_ScoreForLife = 0;

		m_IsGameOver = false;
		m_GainedLife = false;
		m_LostLife = false;
	};

	auto level2 = [this]()->void
	{
		m_EmeraldCount = 21;
		m_EnemyCount = 7;
	};

	auto level3 = [this]()->void
	{
		m_EmeraldCount = 26;
		m_EnemyCount = 9;
	};

	m_Actions = std::map<uint32_t, std::function<void()>>
	{ 
		{0, emeraldCollected},
		{1, enemyKilled}, 
		{2, goldCollected},
		{3, lifeLost}, 
		{4, extraLife}, 
		{5, emeraldStreak},
		{6, level1},
		{7, level2},
		{8, level3}
	};
}

void PlayerStatsSystem::Update()
{
	if (m_ScoreForLife >= 5000)
	{
		OnNotify(4);
	}

	if (m_EmeraldStreak == 8)
	{
		OnNotify(5);
	}
}

void PlayerStatsSystem::AddScore(unsigned int value)
{
	m_TotalScore += value;
	m_ScoreForLife += value;
}
