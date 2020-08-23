#include "DoritoPCH.h"
#include "ResourceManager.h"
#include <filesystem>

#include "Renderer.h"

void ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	//Load all necessary textures and fonts beforehand here
	for (auto& it : std::filesystem::recursive_directory_iterator(m_DataPath))
	{
		std::stringstream ss;
		ss << it.path();
		LoadResources(ss.str());
	}

	PostLoad();
}

sf::Sprite* ResourceManager::LoadSprite(const std::string& file)
{
	sf::Texture* pTexture = (*m_pTextures.find(file)).second;
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
	sf::Font* font = (*m_pFonts.find(file)).second;
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

void ResourceManager::LoadTexture(const std::string& file)
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

		const auto& fullPath = m_DataPath + file;

		if (!pTexture->loadFromFile(fullPath))
		{
			throw  std::runtime_error(std::string("Failed to load texture: " + fullPath));
		}

		m_pTextures.emplace(file, pTexture);
	}
}

void ResourceManager::LoadFont(const std::string& file)
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
		const auto& fullPath = m_DataPath + file;

		if (!pFont->loadFromFile(fullPath))
		{
			throw  std::runtime_error(std::string("Failed to load font: " + fullPath));
		}

		m_pFonts.emplace(file, pFont);
	}
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

void ResourceManager::LoadResources(const std::string& path)
{
	auto lastDot = path.find_last_of('.');
	auto lastBackSlash = path.find_last_of('\\');

	if (lastDot == -1)
		return;

	auto fileType = path.substr(lastDot);
	fileType = fileType.substr(0, fileType.size() - 1);
	
	auto fileName = path.substr(lastBackSlash + 2, (lastDot - lastBackSlash) - 2);

	auto lastSlash = fileName.find_last_of('/');
	fileName = fileName.substr(lastSlash + 1);

	if (fileType == ".png")
	{
		auto loadFunc = std::bind(&ResourceManager::LoadTexture, this, std::placeholders::_1);
		m_pFutures.push_back(std::async(std::launch::async, loadFunc, fileName + fileType));
	}
	else if (fileType == ".otf")
	{
		auto loadFunc = std::bind(&ResourceManager::LoadFont, this, std::placeholders::_1);
		m_pFutures.push_back(std::async(std::launch::async, loadFunc, fileName + fileType));
	}
}

void ResourceManager::PostLoad()
{
	for (auto& thread : m_pFutures)
	{
		thread.get();
	}
}
