#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"

#include "SFML/Graphics.hpp"

void Renderer::Init(sf::Window* window)
{
	(void)window;
	//m_pRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//if (m_pRenderer == nullptr) 
	//{
	//	throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	//}
}

void Renderer::Render() const
{
	//SDL_RenderClear(m_pRenderer);

	//SceneManager::GetInstance().Render();
	//
	//SDL_RenderPresent(m_pRenderer);
}

void Renderer::Destroy()
{
	//if (m_pRenderer != nullptr)
	//{
	//	SDL_DestroyRenderer(m_pRenderer);
	//	m_pRenderer = nullptr;
	//}
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	(void)texture;
	(void)x;
	(void)y;


	//SDL_Rect dst;
	//dst.x = static_cast<int>(x);
	//dst.y = static_cast<int>(y);
	//SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	//SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	(void)texture;
	(void)x;
	(void)y;
	(void)width;
	(void)height;

	//SDL_Rect dst;
	//dst.x = static_cast<int>(x);
	//dst.y = static_cast<int>(y);
	//dst.w = static_cast<int>(width);
	//dst.h = static_cast<int>(height);
	//SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}
