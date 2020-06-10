#include "DoritoPCH.h"
#include "ResourceManager.h"

#include "Renderer.h"

void ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;
}

sf::Sprite* ResourceManager::LoadSprite(const std::string& file)
{
	sf::Texture* pTexture = new sf::Texture();

	m_pTextures.push_back(pTexture);

	const auto fullPath = m_DataPath + file;

	if (!pTexture->loadFromFile(fullPath))
	{
		throw  std::runtime_error(std::string("Failed to load texture: " + fullPath));
	}

	sf::Sprite* pSprite = new sf::Sprite(*pTexture);

	m_pSprites.push_back(pSprite);

	return pSprite;
}

sf::Text* ResourceManager::LoadText(const std::string& text, const std::string& file, unsigned int size)
{
	sf::Font* font = new sf::Font();

	m_pFonts.push_back(font);

	auto fullPath = m_DataPath + file;

	if (!font->loadFromFile(m_DataPath + file))
	{
		throw std::runtime_error(std::string("Failed to load font" + fullPath));
	}

	sf::Text* pText = new sf::Text(text, *font, size);

	m_pText.push_back(pText);

	return pText;
}

void ResourceManager::Destroy()
{
	for (auto sprite : m_pSprites)
	{
		SafeDelete(sprite);
	}

	for (auto text : m_pText)
	{
		SafeDelete(text);
	}

	for (auto texture : m_pTextures)
	{
		SafeDelete(texture);
	}

	for (auto font : m_pFonts)
	{
		SafeDelete(font);
	}
}
