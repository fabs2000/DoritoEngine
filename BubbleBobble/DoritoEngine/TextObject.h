#pragma once
#include "GameObject.h"
#include "Transform.h"

class Font;
class Texture2D;

class TextObject final : public GameObject
{
public:
	void Update(float dt) override;
	void Render() const override;

	void SetText(const std::string& textToDisplay);
	void SetFont(const std::string& fontName);

	explicit TextObject();
	virtual ~TextObject();

	TextObject(const TextObject& other) = delete;
	TextObject(TextObject&& other) = delete;
	TextObject& operator=(const TextObject& other) = delete;
	TextObject& operator=(TextObject&& other) = delete;
private:
	bool m_NeedsUpdate;

	std::string m_Text;
	std::string m_FontName;

	Font* m_pFont;
};