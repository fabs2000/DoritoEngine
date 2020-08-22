#pragma once
#include "Observer.h"

class PlayerStatsSystem : public Observer
{
public:
	PlayerStatsSystem(uint32_t maxEmeralds, uint32_t maxEnemies);
	~PlayerStatsSystem() = default;

	PlayerStatsSystem(const PlayerStatsSystem& other) = delete;
	PlayerStatsSystem(PlayerStatsSystem&& other) noexcept = delete;
	PlayerStatsSystem& operator=(const PlayerStatsSystem& other) = delete;
	PlayerStatsSystem& operator=(PlayerStatsSystem&& other) noexcept = delete;

	void OnNotify(uint32_t event) override;
	void Update();

	int GetLives() const { return m_Lives; }

	uint32_t GetScore() const { return m_TotalScore; }
	uint32_t GetEmeraldStreak() const { return m_EmeraldStreak; }
	uint32_t GetEmeraldCount() const { return m_EmeraldCount; }
	uint32_t GetEnemyCount() const { return m_EnemyCount; }

	bool GetIsGameOver() const { return m_IsGameOver; }

	bool GetLostLife() const { return m_LostLife; }
	bool GetGainedLife() const { return m_GainedLife; }

private:
	int m_Lives;

	uint32_t m_TotalScore
		, m_ScoreForLife;

	uint32_t m_EmeraldCount
		, m_EmeraldStreak;

	uint32_t m_EnemyCount;

	bool m_IsGameOver
		, m_LostLife
		, m_GainedLife;

	std::map<uint32_t, std::function<void()>> m_Actions;

	std::map<std::string, uint32_t> m_HighScores;

	void InitFunctions();
	void AddScore(unsigned int value);
};

