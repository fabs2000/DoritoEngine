#pragma once
#include "Singleton.h"

class Texture2D;
class CustomFont;
class ResourceManager
{
public:
	static ResourceManager& GetInstance()
	{
		static ResourceManager instance{};
		return instance;
	}

	void Init(const std::string& data);
	Texture2D* LoadTexture(const std::string& file) const;
	CustomFont* LoadFont(const std::string& file, unsigned int size) const;

private:

	ResourceManager() = default;
	std::string m_DataPath;
};