#include "pch.h"
#include "Unit.h"
#include <cstdlib>

Unit::Unit()
{
}


Unit::Unit(SDL_Renderer * gRenderer) :
	isSelected(false),
	isMoving(false)
{
	loadMediaUnit(gRenderer);
	reset();
	
	offSetX = randomFloat(-20, 20);
	offSetY = randomFloat(-20,20);
	printf("Display on : %f %f\n", uPosX, uPosY);
}

float Unit::getUPosX()
{
	return uPosX;
}

float Unit::getUPosY()
{
	return uPosY;
}

void Unit::setUPosX(float f)
{
	uPosX = f;
}

void Unit::setUPosY(float f)
{
	uPosY = f;
}

float Unit::getUPosToX()
{
	return toX;
}

float Unit::getUPosToY()
{
	return toY;
}

void Unit::setUPosToX(float f)
{
	toX = f;
}

void Unit::setUPosToY(float f)
{
	toY = f;
}

float Unit::getIsMoving()
{
	return isMoving;
}

float Unit::getSelected()
{
	return isSelected;
}

void Unit::setSelected(bool b)
{
	isSelected = b;
}

bool Unit::isInSelection(SDL_Rect r)
{
	bool b = false;

	if (r.x <= uPosX && r.x + r.w >= uPosX)
	{
		if (r.y <= uPosY && r.y + r.h >= uPosY)
		{
			b = true;
		}
	}
	return b;
}

float Unit::randomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

bool Unit::loadMediaUnit(SDL_Renderer * gRenderer)
{
	//Loading success flag
	Loaded = true;

	//Load Car texture
	if (!unitTexture.loadFromFile("dot.bmp", gRenderer))
	{
		printf("Failed to load dot texture!\n");
		Loaded = false;
	}

	return Loaded;
}

void Unit::move(float timeStep)
{
	if (uPosX != toX + offSetX)
	{	
		isMoving = true;
		//TODO
		//float xAng = toX - uPosX + offSetX;
		//float yAng = toY - uPosY + offSetY;
		//float tan = atan2(yAng, xAng);

		//float tan = atan2(uPosX, toX + offSetX);
		//uPosX = tan;
		if (uPosX > toX + offSetX)
		{
			uPosX -= c.getVelUnit() * timeStep;	
		}
		else
		{
			uPosX += c.getVelUnit() * timeStep;
		}

		if (fabs(uPosX - toX + offSetX) <= 0.5f)
		{
			uPosX = toX + offSetX;
		}
	}
	else
	{
		isMoving = false;
	}

	if (uPosY != toY + offSetY)
	{
		isMoving = true;
		//TODO
		//float tan = atan2(uPosY, toY + offSetY);
		//uPosY = tan;

		if (uPosY > toY + offSetY)
		{
			uPosY -= c.getVelUnit() * timeStep;
		}
		else
		{
			uPosY += c.getVelUnit() * timeStep;
		}

		if (fabs(uPosY - toY + offSetY) <= 0.5f)
		{
			uPosY = toY + offSetY;
		}
	}
	else
	{
		isMoving = false;
	}
}

void Unit::render(SDL_Renderer* gRenderer)
{
	if (!Loaded || !unitTexture.loadFromFile("dot.bmp", gRenderer))
	{
		printf("Failed to load dot texture!\n");
		//Loaded = false;
	}

	if (getSelected() == true)
	{
		SDL_Rect lasso;

		lasso.x = uPosX - 1;
		lasso.y = uPosY - 1;
		lasso.w = c.getUnitWidth() + 2;
		lasso.h = c.getUnitHeight() + 2;

		//printf("Lasso : %f, %f, %f, %f\n", xStart, yStart, xEnd, yEnd);

		//Render rext
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(gRenderer, &lasso);
	}

	unitTexture.render((int)uPosX, (int)uPosY, gRenderer);

}

void Unit::reset()
{
	float randX = randomFloat(0, (float)c.getScreenWidth() / 2);
	float randY = randomFloat(0, (float)c.getScreenHeight() / 2);

	uPosX = randX;
	uPosY = randY;

	toX = randX;
	toY = randY;
}
