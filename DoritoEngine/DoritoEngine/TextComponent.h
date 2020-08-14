#pragma once
#include "BaseComponent.h"
#include <SFML/Graphics.hpp>

class TextComponent final : public BaseComponent
{
public:
	explicit TextComponent(const std::string& text, const std::string& file, unsigned int size);

	void SetText(const std::string& textToDisplay);
	void SetSize(unsigned int size);
	void SetColor(const sf::Color& color);
	void SetFont(const std::string& fontName);

	TextComponent(const TextComponent&) = delete;
	TextComponent(TextComponent&&) = delete;
	TextComponent& operator= (const TextComponent&) = delete;
	TextComponent& operator= (const TextComponent&&) = delete;

	////Fix this dumb shit ples
	//const sf::FloatRect& GetCollisionRect() const { return m_pText->getGlobalBounds(); };

protected:
	void Initialize() override;
	void Update(float dt) override;
	void Render() override;

private:
	sf::Text* m_pText;
};
