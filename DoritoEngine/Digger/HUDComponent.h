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

	TextComponent* m_pTextComp
		, * m_pScoreComp;

	std::vector<SpriteComponent*> m_pLivesSprite;

	Scene* m_pSceneRef;

	PlayerStatsSystem* m_pGameStats;
};

