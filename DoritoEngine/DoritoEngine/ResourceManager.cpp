#include "DoritoPCH.h"
#include "ResourceManager.h"

#include "Renderer.h"

void ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;
}

sf::Sprite* ResourceManager::LoadSprite(const std::string& file)
{
	sf::Texture* pTexture = LoadTexture(file);
	sf::Sprite* pSprite = nullptr;

	auto it = m_pSprites.find(pTexture);

	//Same logic for sprites as with textures, just textures are the keys for the sprites
	if (it != m_pSprites.end())
	{
		pSprite = (*it).second;
	}
	else
	{
		pSprite = new sf::Sprite(*pTexture);
		m_pSprites.emplace(pTexture, pSprite);
	}
	return pSprite;
}

sf::Text* ResourceManager::LoadText(const std::string& text, const std::string& file, unsigned int size)
{
	sf::Font* font = LoadFont(file);
	sf::Text* pText = nullptr;

	auto it = m_pTexts.find(text);

	if (it != m_pTexts.end())
	{
		pText = (*it).second;
	}
	else
	{
		pText = new sf::Text(text, *font, size);
		m_pTexts.emplace(text, pText);
	}
	return pText;
}

sf::Texture* ResourceManager::LoadTexture(const std::string& file)
{
	sf::Texture* pTexture = nullptr;
	auto it = m_pTextures.find(file);

	//If Texture has been loaded pointed to return is assigned
	if (it != m_pTextures.end())
	{
		pTexture = (*it).second;
	}
	//Else create new texture
	else
	{
		pTexture = new sf::Texture();
		m_pTextures.emplace(file, pTexture);

		const auto& fullPath = m_DataPath + file;

		if (!pTexture->loadFromFile(fullPath))
		{
			throw  std::runtime_error(std::string("Failed to load texture: " + fullPath));
		}
	}

	return pTexture;
}

sf::Font* ResourceManager::LoadFont(const std::string& file)
{
	sf::Font* pFont = nullptr;
	auto it = m_pFonts.find(file);

	//If Texture has been loaded pointed to return is assigned
	if (it != m_pFonts.end())
	{
		pFont = (*it).second;
	}
	//Else create new texture
	else
	{
		pFont = new sf::Font();
		m_pFonts.emplace(file, pFont);

		const auto& fullPath = m_DataPath + file;

		if (!pFont->loadFromFile(fullPath))
		{
			throw  std::runtime_error(std::string("Failed to load font: " + fullPath));
		}
	}

	return pFont;
}

void ResourceManager::Destroy()
{
	for (auto& sprite : m_pSprites)
	{
		SafeDelete(sprite.second);
	}

	for (auto& text : m_pTexts)
	{
		SafeDelete(text.second);
	}

	for (auto& texture : m_pTextures)
	{
		SafeDelete(texture.second);
	}

	for (auto& font : m_pFonts)
	{
		SafeDelete(font.second);
	}
}
