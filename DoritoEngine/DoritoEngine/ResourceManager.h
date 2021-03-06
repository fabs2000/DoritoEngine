#pragma once
#include "Singleton.h"
#include <map>
#include <future>

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
	void LoadTexture(const std::string& file);
	void LoadFont(const std::string& file);

	void Destroy();

private:

	ResourceManager() = default;
	std::string m_DataPath;

	std::map<std::string, sf::Texture*> m_pTextures;
	std::map< sf::Texture*, sf::Sprite*> m_pSprites;

	std::map<std::string, sf::Font*> m_pFonts;
	std::map<std::string, sf::Text*> m_pTexts;
	
	std::vector<std::future<void>> m_pFutures;

	void LoadResources(const std::string& path);
	void PostLoad();
};