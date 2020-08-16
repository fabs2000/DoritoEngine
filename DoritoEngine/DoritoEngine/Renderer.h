#pragma once
#include "Singleton.h"
#include "DoritoEngine.h"
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
	void RenderShape(const sf::Shape& shapeToDraw);

	sf::RenderWindow& GetRenderer() { return m_pRenderer; };

	void SetDebugRendering(bool isOn) { m_IsDebugRenderingOn = isOn; }
	bool GetDebugRendering() { return m_IsDebugRenderingOn; }

private:
	sf::RenderWindow m_pRenderer;

	bool m_IsDebugRenderingOn = false;
};
