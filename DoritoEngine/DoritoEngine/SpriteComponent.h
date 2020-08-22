#pragma once
#include "BaseComponent.h"
#include <SFML/Graphics.hpp>

struct AnimationInfo
{
	AnimationInfo(bool isAnimating = false, const sf::Vector2u& columnsRows = sf::Vector2u(), float animRate = 0.f, unsigned int row = 0) 
		: IsAnimating(isAnimating)
		, ColumnsRows(columnsRows)
		, CurrentPos()
		, AnimRate(animRate)
		, AnimTime()
		, UV()
		, Row(row)
	{}

	bool IsAnimating = false;
	sf::Vector2u ColumnsRows;
	sf::Vector2u CurrentPos;

	float AnimRate;
	float AnimTime;

	sf::IntRect UV;

	unsigned int Row;
};

class SpriteComponent : public BaseComponent
{
public:
	explicit SpriteComponent(const std::string& file, bool isCentered = true, bool isUsingRelativeTrans = false, AnimationInfo animInfo = AnimationInfo());

	SpriteComponent(const SpriteComponent&) = delete;
	SpriteComponent(SpriteComponent&&) = delete;
	SpriteComponent& operator= (const SpriteComponent&) = delete;
	SpriteComponent& operator= (const SpriteComponent&&) = delete;

	const sf::FloatRect& GetBounds() const { return m_Bounds; }

	void SetTexture(const std::string& file);
	void SetIsAnimating(bool isAnimating) { m_AnimationInfo.IsAnimating = isAnimating; }
	void SetAnimRow(unsigned int row) { m_AnimationInfo.Row = row; }

	void SetCanRender(bool canRender) { m_CanRender = canRender; }

protected:
	void Initialize() override;
	void Update(float dt) override;
	void Render() override;

private:
	sf::Sprite* m_pSprite;
	sf::FloatRect m_Bounds;

	bool m_IsCentered;
	bool m_UsingRelativeTrans;
	bool m_CanRender;

	AnimationInfo m_AnimationInfo;
	sf::IntRect m_OriginalUV;

	void PlayAnimation(float dt);
};
