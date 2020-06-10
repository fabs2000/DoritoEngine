#pragma once
#include "Singleton.h"
#include "../BubbleBobble/Game.h"
#include "SFML/Graphics.hpp"

class SpriteComponent;
class TransformComponent;

class Renderer final
{
public:

	static Renderer* GetInstance()
	{
		static Renderer instance{};
		return &instance;
	}

	void Init(const GameInfo::WindowSettings& windowSettings);
	void Render();

	void RenderTexture(sf::Sprite* texture, TransformComponent* transform);
	void RenderText(sf::Text* pText, TransformComponent* transform);

	sf::RenderWindow& GetRenderer() { return m_pRenderer; };

private:
	sf::RenderWindow m_pRenderer;
};
