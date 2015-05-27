/*
 * Text.h
 *
 *  Created on: 21/05/2015
 *      Author: Pedro2
 */

#ifndef ENGINE_TEXT_H_
#define ENGINE_TEXT_H_

#include <SDL_pixels.h>
#include <SDL_ttf.h>
#include <string>

#include "Geometry/Rect.h"

class Text {
public:
	enum TextStyle{
		SOLID,
		SHADED,
		BLENDED
	};
	Text(std::string fontFile,
			int fontSize,
			TextStyle style,
			std::string text,
			SDL_Color color,
			int x = 0,
			int y = 0);
	virtual ~Text();

	void Render(int cameraX = 0, int cameraY = 0);
	void SetPos(int x, int y,
			bool centerX = false, bool centerY = false);

	void SetText(std::string text);
	void SetColor(SDL_Color color);
	void SetStyle(TextStyle style);
	void SetFontSize(int fontSize);
private:
	void RemakeTexture();

	TTF_Font* font;
	SDL_Texture* texture;

	std::string text;
	TextStyle style;
	int fontSize;
	SDL_Color color;
	Rect box;
};

#endif /* ENGINE_TEXT_H_ */
