#include "pch.h"
#include "Unit.h"
#include <cstdlib>

Unit::Unit()
{
}


Unit::Unit(SDL_Renderer * gRenderer)
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

		if (fabs(uPosX - toX + offSetX) < 2.0f)
		{
			toX = uPosX - offSetX;
		}
	}

	if (uPosY != toY + offSetY)
	{
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

		if (fabs(uPosY - toY + offSetY) < 2.0f)
		{
			toY = uPosY - offSetY;
		}
	}
}

void Unit::render(SDL_Renderer* gRenderer)
{
	if (!Loaded || !unitTexture.loadFromFile("dot.bmp", gRenderer))
	{
		printf("Failed to load dot texture!\n");
		//Loaded = false;
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
