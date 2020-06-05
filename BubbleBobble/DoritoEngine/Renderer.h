#pragma once
#include "Singleton.h"
#include "SFML/Graphics/RenderWindow.hpp"

class Texture2D;
/**
 * Simple RAII wrapper for the SFML renderer
 **/

using namespace sf;

class Renderer final : public Singleton<Renderer>
{
public:
	void Init(Window* window);
	void Render() const;
	void Destroy();

	void RenderTexture(const Texture2D& texture, float x, float y) const;
	void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

	sf::RenderWindow* GetSDLRenderer() const { return m_pRenderer; }
private:
	sf::RenderWindow* m_pRenderer{};
};
