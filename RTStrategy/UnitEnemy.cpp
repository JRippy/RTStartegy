#include "pch.h"
#include "UnitEnemy.h"


UnitEnemy::UnitEnemy()
{
}

UnitEnemy::UnitEnemy(SDL_Renderer * gRenderer):
	isSelected(false),
	isDead(false)
{
	loadMediaUnit(gRenderer);
	reset();

	//Set collision circle size
	mCollider.r = c.getUnitWidth() * 2;

	//offSetX = randomFloat(-20, 20);
	//offSetY = randomFloat(-20,20);
	setUOffsetX(0);
	setUOffsetX(0);
	isPathFound(false);
	printf("Display Enemy on : %f %f\n", uPosX, uPosY);
}


UnitEnemy::~UnitEnemy()
{
}

bool UnitEnemy::loadMediaUnit(SDL_Renderer * gRenderer)
{
	//Loading success flag
	Loaded = true;

	//Load Car texture
	if (!unitTexture.loadFromFile("dot_Enemy.bmp", gRenderer))
	{
		printf("Failed to load dot enemy texture!\n");
		Loaded = false;
	}

	return Loaded;
}

void UnitEnemy::render(SDL_Renderer * gRenderer)
{

	if (!isDead)
	{

		if (!Loaded || !unitTexture.loadFromFile("dot_Enemy.bmp", gRenderer))
		{
			printf("Failed to load dot enemy texture!\n");
		}
	}
	else
	{
		if (!unitTexture.loadFromFile("dot_Dead.bmp", gRenderer))
		{
			printf("Failed to load dot dead enemy texture!\n");
		}
	}

	if (getSelected() == true)
	{
		SDL_Rect lasso;

		lasso.x = uPosX - 1;
		lasso.y = uPosY - 1;
		lasso.w = c.getUnitWidth() + 2;
		lasso.h = c.getUnitHeight() + 2;

		//Render rext
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(gRenderer, &lasso);
	}

	unitTexture.render((int)uPosX, (int)uPosY, gRenderer);
}

void UnitEnemy::reset()
{
	float randX = randomFloat((float)c.getScreenWidth() * 3 / 4, (float)c.getScreenWidth());
	float randY = randomFloat((float)c.getScreenHeight() * 3 / 4, (float)c.getScreenHeight());

	setUPosX(randX);
	setUPosY(randY);

	uMidX = uPosX + c.getUnitWidth() / 2;
	uMidY = uPosY + c.getUnitHeight() / 2;

	setUPosToX(randX);
	setUPosToY(randY);

	setUOffsetX(0);
	setUOffsetY(0);
}

float UnitEnemy::randomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}