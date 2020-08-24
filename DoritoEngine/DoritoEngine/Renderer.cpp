#include "DoritoPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Transform.h"

#include "SFML/Graphics.hpp"

void Renderer::Init(const GameInfo::WindowSettings& windowSettings)
{
	m_pRenderer.create(sf::VideoMode(windowSettings.width, windowSettings.height), windowSettings.title,
		sf::Style::Titlebar | sf::Style::Close);

	if (!m_pRenderer.isOpen())
	{
		throw std::runtime_error(std::string("SFML Window not created"));
	}

	m_pRenderer.setVerticalSyncEnabled(windowSettings.isVsyncOn);
	m_FrameCap = windowSettings.frameCap;

	m_pRenderer.setFramerateLimit(m_FrameCap);
}

void Renderer::Render()
{
	m_pRenderer.clear();

	SceneManager::GetInstance()->Render();

	m_pRenderer.display();
}

void Renderer::RenderSprite(sf::Sprite* pSprite, TransformComponent* transform)
{
	m_pRenderer.draw(*pSprite, transform->GetBaseTransform());
}

void Renderer::RenderText(sf::Text* pText, TransformComponent* transform)
{
	m_pRenderer.draw(*pText, transform->GetBaseTransform());
}

void Renderer::RenderShape(const sf::Shape& shapeToDraw)
{
	if (m_IsDebugRenderingOn)
		m_pRenderer.draw(shapeToDraw);
}
