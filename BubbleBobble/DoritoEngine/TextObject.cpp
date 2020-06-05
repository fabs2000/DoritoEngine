#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "ResourceManager.h"

TextObject::TextObject()
	: m_NeedsUpdate{ true }
	, m_Text{}
	, m_FontName{}
	, m_pFont{ nullptr }
{ 
	m_pTexture = nullptr;
}

TextObject::~TextObject()
{
	if (m_pFont != nullptr)
	{
		delete m_pFont;
		m_pFont = nullptr;
	}
}

void TextObject::Update(float dt)
{
	//TODO: REMOVE BLYAT
	(void)dt;

	//if (m_NeedsUpdate)
	//{
	//	const SDL_Color color = { 255,255,255 }; // only white text is supported now
	//	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
	//	if (surf == nullptr) 
	//	{
	//		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	//	}
	//	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	//	if (texture == nullptr) 
	//	{
	//		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	//	}
	//	SDL_FreeSurface(surf);
	//	m_pTexture = new Texture2D(texture);
	//	m_NeedsUpdate = false;
	//}
}

void TextObject::Render() const
{
	if (m_pTexture != nullptr)
	{
		const auto pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void TextObject::SetText(const std::string& textToDisplay)
{
	m_Text = textToDisplay;
	m_NeedsUpdate = true;
}

void TextObject::SetFont(const std::string& fontName)
{
	(void)fontName;

	//m_pFont = ResourceManager::GetInstance().LoadFont(fontName, 46);
}



