#include "PlayerStatsSystem.h"

void PlayerStatsSystem::OnNotify(Event event)
{
	switch (event)
	{
	case Event::EMERALD_COLLECTED:
		AddScore(25);
		m_EmeraldStreak++;
		break;

	case Event::ENEMY_KILLED:
		AddScore(250);
		break;

	case Event::GOLD_COLLECTED:
		AddScore(500);
		break;

	case Event::LIFE_LOST:
		m_Lives--;
		break;

	case Event::EXTRA_LIFE:
		m_ScoreForLife = 0;

		if (m_Lives < 3)
			m_Lives++;

		break;
	}
}

void PlayerStatsSystem::Update()
{
	if (m_ScoreForLife >= 20000)
	{
		OnNotify(Event::EXTRA_LIFE);
	}
}

void PlayerStatsSystem::AddScore(unsigned int value)
{
	m_TotalScore += value;
	m_ScoreForLife += value;
}
