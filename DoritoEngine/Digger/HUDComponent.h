#pragma once
#include "BaseComponent.h"

class SpriteComponent;
class TextComponent;
class PlayerStatsSystem;
class Scene;

class HUDComponent : public BaseComponent
{
public:
	HUDComponent();
	~HUDComponent() = default;

protected:
	void Initialize() override;
	void Update(float) override;
	void Render() override;

private:

	uint32_t m_Score
		, m_Lives;

	TextComponent* m_pTextComp
		, * m_pScoreComp;

	SpriteComponent* m_pLivesSprite;

	Scene* m_pSceneRef;

	PlayerStatsSystem* m_pGameStats;
};

