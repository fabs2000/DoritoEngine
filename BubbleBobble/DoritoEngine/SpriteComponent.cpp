#include "DoritoPCH.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "Transform.h"

#include "ResourceManager.h"
#include "Renderer.h"

SpriteComponent::SpriteComponent(const std::string& file, bool isCentered, AnimationInfo animInfo)
	: m_pSprite(ResourceManager::GetInstance()->LoadSprite(file))
	, m_IsCentered( isCentered )
	, m_AnimationInfo( animInfo )
{
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Initialize()
{
	if (m_IsCentered)
	{
		float newX = static_cast<float>(m_pSprite->getTexture()->getSize().x/2);
		float newY = static_cast<float>(m_pSprite->getTexture()->getSize().y/2);

		GetParentTransform()->SetOrigin(newX, newY);
	}
	else
	{
		float newY = static_cast<float>(m_pSprite->getTexture()->getSize().y);

		GetParentTransform()->SetOrigin(0, newY);
	}

	//Not functional
	if (m_AnimationInfo.IsAnimating)
	{
		m_AnimationInfo.UV.left = 0;
		m_AnimationInfo.UV.top = m_AnimationInfo.Row * m_AnimationInfo.UV.height;
		m_AnimationInfo.UV.width = m_pSprite->getTexture()->getSize().x / (m_AnimationInfo.ColumnsRows.x);
		m_AnimationInfo.UV.height = m_pSprite->getTexture()->getSize().y / (m_AnimationInfo.ColumnsRows.y);

		m_OriginalUV = sf::IntRect(m_AnimationInfo.UV);
	}
}

void SpriteComponent::Update(float dt)
{
	//Not functional
	if (m_AnimationInfo.IsAnimating)
		PlayAnimation(dt);

	m_Bounds = GetParentTransform()->GetBaseTransform().transformRect(m_pSprite->getGlobalBounds());
}

void SpriteComponent::Render()
{
	Renderer::GetInstance()->RenderTexture(m_pSprite, GetParentTransform());
}

void SpriteComponent::PlayAnimation(float dt)
{
	m_AnimationInfo.CurrentPos.y = m_AnimationInfo.Row;

	m_AnimationInfo.AnimTime += dt;

	if (m_AnimationInfo.AnimTime >= m_AnimationInfo.AnimRate)
	{
		m_AnimationInfo.AnimTime -= m_AnimationInfo.AnimRate;
		m_AnimationInfo.CurrentPos.x++;

		if (m_AnimationInfo.CurrentPos.x >= m_AnimationInfo.ColumnsRows.x)
		{
			m_AnimationInfo.CurrentPos.x = 0;
		}
	}

	m_AnimationInfo.UV.left = m_AnimationInfo.CurrentPos.x * m_AnimationInfo.UV.width;
	m_AnimationInfo.UV.top = m_AnimationInfo.CurrentPos.y * m_AnimationInfo.UV.height;

	m_pSprite->setTextureRect(m_AnimationInfo.UV);
}