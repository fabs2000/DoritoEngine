#include "DoritoPCH.h"
#include "TextComponent.h"

#include "ResourceManager.h"
#include "Renderer.h"

TextComponent::TextComponent(const std::string& text, const std::string& file, unsigned int size)
	: m_pText(ResourceManager::GetInstance()->LoadText(text, file, size))
{
}

void TextComponent::Initialize()
{}

void TextComponent::Update(float dt)
{
	dt;
}

void TextComponent::Render()
{
	Renderer::GetInstance()->RenderText(m_pText, GetParentTransform());
}

void TextComponent::SetText(const std::string& textToDisplay)
{
	m_pText->setString(textToDisplay);
}

void TextComponent::SetSize(unsigned int size)
{
	m_pText->setCharacterSize(size);
}



