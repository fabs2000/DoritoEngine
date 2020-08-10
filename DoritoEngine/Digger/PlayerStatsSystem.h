#pragma once
#include "Observer.h"

class PlayerStatsSystem : public Observer
{
public:
	PlayerStatsSystem() 
		: m_TotalScore()
		, m_EmeraldStreak()
		, m_ScoreForLife()
		, m_Lives(1) 
	{}
	~PlayerStatsSystem() = default;

	PlayerStatsSystem(const PlayerStatsSystem& other) = delete;
	PlayerStatsSystem(PlayerStatsSystem&& other) noexcept = delete;
	PlayerStatsSystem& operator=(const PlayerStatsSystem& other) = delete;
	PlayerStatsSystem& operator=(PlayerStatsSystem&& other) noexcept = delete;

	void OnNotify(Event event) override;

	unsigned int GetScore() const { return m_TotalScore; }
	unsigned int GetLives() const { return m_Lives; }
	unsigned int GetEmeraldStreak() const { return m_EmeraldStreak; }

	void Update();

private:
	unsigned int m_TotalScore;
	unsigned int m_ScoreForLife;

	unsigned int m_EmeraldStreak;
	unsigned int m_Lives;

	void AddScore(unsigned int value);
};

