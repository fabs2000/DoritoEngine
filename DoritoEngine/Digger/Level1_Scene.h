#pragma once
#include "Scene.h"

enum class LevelState
{
	LEVEL_1 = 0,
	LEVEL_2 = 1,
	LEVEL_3 = 2
};

class TextComponent;
class PlayerStatsSystem;
class GameObject;

class Level_1 : public Scene
{
public:
	Level_1(const std::string& sceneName, const GameInfo& gameInfo);

	virtual ~Level_1() = default;
	Level_1(const Level_1& other) = delete;
	Level_1(Level_1&& other) = delete;
	Level_1& operator=(const Level_1& other) = delete;
	Level_1& operator=(Level_1&& other) = delete;

	void Initialize() override;
	void Update(float dt) override;
	void Render() const override;

private:
	TextComponent* m_pTextComp;

	PlayerStatsSystem* m_pGameStats;

	GameObject* m_pDigger;
	GameObject* m_pEnemyPlayer;
	
	int m_FPSNb;

	float m_EnemySpawnTimer;
	int m_MaxEnemies
		, m_EnemyCount;

	LevelState m_GameState;

	sf::Vector2f m_EnemySpawnPos;

	void ResetToLevel1();
	void SetLevel2();
	void SetLevel3();

	void EnemySpawner(float dt);

	bool m_FirstLevelInit
		, m_SecondPlayerJoined;
};

