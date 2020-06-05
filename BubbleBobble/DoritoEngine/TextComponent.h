#pragma once
#include <SDL.h>
#include <SDL_ttf.h>


class CustomFont;
class Texture2D;
class TextComponent final
{
public:
	~TextComponent();

	void Update();
	void Render(float posX, float posY) const;

	void InitText(const std::string& text, CustomFont* font, const SDL_Color& color);
	void SetText(const std::string& text);

private:
	bool m_NeedsUpdate;
	std::string m_Text;
	CustomFont* m_Font;
	Texture2D* m_Texture;
	SDL_Color m_Color;
};