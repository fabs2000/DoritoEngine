#pragma once
#include "Singleton.h"

class ResourceManager
{
public:

	static ResourceManager* GetInstance()
	{
		static ResourceManager instance{};
		return &instance;
	}

	void Init(const std::string& data);
	
	sf::Sprite* LoadSprite(const std::string& file);
	sf::Text* LoadText(const std::string& text, const std::string& file, unsigned int size);

	sf::Texture* LoadTexture(const std::string& file);

	void Destroy();

private:

	ResourceManager() = default;
	std::string m_DataPath;

	std::vector<sf::Texture*> m_pTextures;
	std::vector<sf::Sprite*> m_pSprites;

	std::vector<sf::Font*> m_pFonts;
	std::vector<sf::Text*> m_pText;
};