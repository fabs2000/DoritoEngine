#pragma once
#include "Scene.h"

class TextComponent;
class PlayerStatsSystem;

class TestScene : public Scene
{
public:

	TestScene(const std::string& sceneName, const GameInfo& gameInfo);

	virtual ~TestScene() = default;
	TestScene(const TestScene& other) = delete;
	TestScene(TestScene&& other) = delete;
	TestScene& operator=(const TestScene& other) = delete;
	TestScene& operator=(TestScene&& other) = delete;

	void Initialize() override;
	void PostInitialize() override;

	void Update(float dt) override;
	void Render() const override;

private:
	TextComponent* m_pTextComp
		,* m_pScoreComp;

	PlayerStatsSystem* m_pGameStats;

	int m_FPSNb;
};

