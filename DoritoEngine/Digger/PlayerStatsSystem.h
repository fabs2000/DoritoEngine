#pragma once
#include "Observer.h"

class PlayerStatsSystem : public Observer
{
public:
	PlayerStatsSystem();
	~PlayerStatsSystem() = default;

	PlayerStatsSystem(const PlayerStatsSystem& other) = delete;
	PlayerStatsSystem(PlayerStatsSystem&& other) noexcept = delete;
	PlayerStatsSystem& operator=(const PlayerStatsSystem& other) = delete;
	PlayerStatsSystem& operator=(PlayerStatsSystem&& other) noexcept = delete;

	void OnNotify(uint32_t event) override;

	uint32_t GetScore() const { return m_TotalScore; }
	uint32_t GetLives() const { return m_Lives; }
	uint32_t GetEmeraldStreak() const { return m_EmeraldStreak; }

	void InitFunctions();
	void Update();

private:
	uint32_t m_TotalScore;
	uint32_t m_ScoreForLife;

	uint32_t m_EmeraldStreak;
	uint32_t m_Lives;

	bool m_IsGameOver;

	std::map<uint32_t, std::function<void()>> m_Actions;

	void AddScore(unsigned int value);
};

