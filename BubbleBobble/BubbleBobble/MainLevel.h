#pragma once
#include "Scene.h"

class TextComponent;

class MainLevel : public Scene
{
public:
	MainLevel(const std::string& sceneName, const GameInfo& gameInfo);

	virtual ~MainLevel() = default;
	MainLevel(const MainLevel& other) = delete;
	MainLevel(MainLevel&& other) = delete;
	MainLevel& operator=(const MainLevel& other) = delete;
	MainLevel& operator=(MainLevel&& other) = delete;

	void Initialize() override;
	void Update(float dt) override;
	void Render() const override;

private:
	GameObject* m_pFPS;
	GameObject* m_pPlayer;

	TextComponent* m_pTextComp;

	void Pressed() { std::cout << "Pressed\n"; };
	void Released() { std::cout << "Released\n"; };
	void Down() { std::cout << "Down\n"; };

	int m_FPSNb;
};

