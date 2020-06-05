#pragma once

struct _TTF_Font;

/**
 * Simple RAII wrapper for an _TTF_Font
 */
class CustomFont
{
public:
	_TTF_Font* GetFont() const;
	explicit CustomFont(const std::string& fullPath, unsigned int size);
	~CustomFont();

	CustomFont(const CustomFont&) = delete;
	CustomFont(CustomFont&&) = delete;
	CustomFont& operator= (const CustomFont&) = delete;
	CustomFont& operator= (const CustomFont&&) = delete;
private:
	_TTF_Font* m_Font;
	unsigned int m_Size;
};
