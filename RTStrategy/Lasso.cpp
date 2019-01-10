#include "pch.h"
#include "Lasso.h"


Lasso::Lasso() :
	xStart(0),
	yStart(0),
	xEnd(0),
	yEnd(0),
	press(false),
	resetSelect(false)
{
}


Lasso::~Lasso()
{
}

SDL_Rect Lasso::getSelection()
{
	SDL_Rect lasso;

	lasso.x = xStart;
	lasso.y = yStart;
	lasso.w = xEnd - xStart;
	lasso.h = yEnd - yStart;

	return lasso;
}

//bool Lasso::resetSelection()
//{
//}

void Lasso::handleEvent(SDL_Event & e)
{
	//If a key was pressed
	//if (e.key.keysym.mod && KMOD_LCTRL && e.key.keysym.mod == KMOD_LCTRL)
	//{
	//	/*if (e.type == SDL_MOUSEBUTTONDOWN)
	//	{*/
	//		printf("CTRL_L\n");
	//	//}
	//}

	if (e.key.keysym.mod && KMOD_LCTRL && e.key.keysym.mod == KMOD_LCTRL)
	{
		printf("CTRL\n");
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				mousePress(e.button);
			}
	}


	if (e.type == SDL_MOUSEBUTTONDOWN && press == false)
	{
		mousePress(e.button);
		resetSelect = true;
	}

	if (press == true)
	{
		resetSelect = false;
		mouseDown(e.button);
	}

	if (e.type == SDL_MOUSEBUTTONUP)
	{
		mouseRelease(e.button);
	}
}


void Lasso::mousePress(SDL_MouseButtonEvent& b) {

	if (b.button == SDL_BUTTON_RIGHT) {
		//handle a left-click
		press = true;
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (x <= 0)
		{
			x = 0;
		}
		else if (x < c.getScreenWidth() && x > 0)
		{
			//Adjust position
			x = (float)x;
		}

		if (y <= 0)
		{
			y = 0;
		}
		else if (y < c.getScreenHeight() && y > 0)
		{
			//Adjust position
			y = (float)y;
			//move(timeStep);
		}

		xStart = x;
		yStart = y;

	}
}

void Lasso::mouseDown(SDL_MouseButtonEvent & b)
{
		//handle a left-click
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (x <= 0)
		{
			x = 0;
		}
		else if (x < c.getScreenWidth() && x > 0)
		{
			//Adjust position
			x = (float)x;
		}

		if (y <= 0)
		{
			y = 0;
		}
		else if (y < c.getScreenHeight() && y > 0)
		{
			//Adjust position
			y = (float)y;
		}

		xEnd = x;
		yEnd = y;

}

void Lasso::mouseRelease(SDL_MouseButtonEvent & b)
{
	if (b.button == SDL_BUTTON_RIGHT) {
		//handle a left-click
		press = false;
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (x <= 0)
		{
			x = 0;
		}
		else if (x < c.getScreenWidth() && x > 0)
		{
			//Adjust position
			x = (float)x;
			//move(timeStep);
		}

		if (y <= 0)
		{
			y = 0;
		}
		else if (y < c.getScreenHeight() && y > 0)
		{
			//Adjust position
			y = (float)y;
			//move(timeStep);
		}

		xEnd = x;
		yEnd = y;

	}
}

void Lasso::render(SDL_Renderer* gRenderer)
{
	if (press == true)
	{
		SDL_Rect lasso;

		lasso.x = xStart;
		lasso.y = yStart;
		lasso.w = xEnd - xStart;
		lasso.h = yEnd - yStart;

		//Render racket
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(gRenderer, &lasso);

		//Show the Racket
		lassoTexture.render(lasso.x, lasso.y, gRenderer);
	}

}