#pragma once
#include "Scene.h"

class TextComponent;
class PlayerStatsSystem;

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
	TextComponent* m_pTextComp
		,* m_pScoreComp;

	PlayerStatsSystem* m_pGameStats;

	int m_FPSNb;
};

