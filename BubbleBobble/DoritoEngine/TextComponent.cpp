#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

TextComponent::~TextComponent()
{
	delete m_Texture;
	m_Texture = nullptr;
}

void TextComponent::Update()
{
	if (m_NeedsUpdate && m_Font != nullptr)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = new Texture2D(texture);
		m_NeedsUpdate = false;
	}
}

void TextComponent::InitText(const std::string& text, Font* font, const SDL_Color& color)
{
	m_NeedsUpdate = true;
	m_Text = text; 
	m_Font = font;
	m_Color = color;
}

// This implementation uses the "dirty flag" pattern
void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextComponent::Render(float posX, float posY) const
{
	if (m_Texture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, posX, posY);
	}
}
