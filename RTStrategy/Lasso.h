#include <SDL.h>
#include "Config.h"
#include "Texture.h"

#pragma once
class Lasso
{
public:
	Lasso();
	~Lasso();

	SDL_Rect getSelection();

	//bool resetSelection();

	void handleEvent(SDL_Event & e);
	void mousePress(SDL_MouseButtonEvent& b);
	void mouseDown(SDL_MouseButtonEvent& b);
	void mouseRelease(SDL_MouseButtonEvent& b);

	void render(SDL_Renderer * gRenderer);

private :

	Config c;

	float xStart, yStart;
	float xEnd, yEnd;

	bool press;
	bool resetSelect;

	Texture lassoTexture;
};

