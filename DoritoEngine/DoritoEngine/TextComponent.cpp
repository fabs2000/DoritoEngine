#include "DoritoPCH.h"
#include "TextComponent.h"

#include "ResourceManager.h"
#include "Renderer.h"

TextComponent::TextComponent(const std::string& text, const std::string& file, unsigned int size)
	: m_pText(ResourceManager::GetInstance()->LoadText(text, file, size))
	, m_Text(text)
{
}

void TextComponent::Initialize()
{

}

void TextComponent::Update(float)
{
}

void TextComponent::Render()
{
	Renderer::GetInstance()->RenderText(m_pText, GetParentTransform());
}

void TextComponent::SetText(const std::string& textToDisplay)
{
	m_Text = textToDisplay;
	m_pText->setString(m_Text);
}

void TextComponent::SetSize(unsigned int size)
{
	m_pText->setCharacterSize(size);
}

void TextComponent::SetColor(const sf::Color& color)
{
	m_pText->setFillColor(color);
}



