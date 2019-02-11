#include "pch.h"
#include "UnitGroup.h"


UnitGroup::UnitGroup()
{

}


UnitGroup::UnitGroup(SDL_Renderer* gRenderer)
{	
	numUnit = 0;
	numUnitDead = 0;
	vUnit.reserve(c.getNumUnit());
	vSelectedUnit.reserve(c.getNumUnit());
	vUnitX.reserve(c.getNumUnit());
	vUnitY.reserve(c.getNumUnit());

	numUnitEnemy = 0;
	numUnitEnemyDead = 0;
	vEnemyUnit.reserve(c.getNumUnitEnemy());
	vEnemySelectedUnit.reserve(c.getNumUnitEnemy());
	vEnemyUnitX.reserve(c.getNumUnitEnemy());
	vEnemyUnitY.reserve(c.getNumUnitEnemy());

}

void UnitGroup::handleEvent(SDL_Event & e)
{
	//If a key was pressed
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		mousePress(e.button);
	}
}

void UnitGroup::handleEventEnemy(SDL_Event & e)
{	//If a key was pressed
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		mousePressEnemy(e.button);
	}
}

void UnitGroup::load(SDL_Renderer* gRenderer)
{
	for (size_t i = 0; i < c.getNumUnit(); i++)
	{
		Unit u = Unit(gRenderer);
		printf("Unit i =  %i| X = %f| Y = %f\n", i, u.getUPosX(), u.getUPosY());
		vUnit.push_back(u);
	}	
	
	for (size_t i = 0; i < c.getNumUnitEnemy(); i++)
	{
		UnitEnemy u = UnitEnemy(gRenderer);
		vEnemyUnit.push_back(u);
	}
}

void UnitGroup::render(SDL_Renderer * gRenderer)
{
	for (size_t i = 0; i < c.getNumUnit(); i++)
	{
		Unit u = vUnit[i];
		u.render(gRenderer);
	}

	for (size_t i = 0; i < c.getNumUnitEnemy(); i++)
	{
		UnitEnemy uE = vEnemyUnit[i];
		uE.render(gRenderer);
	}
}

void UnitGroup::mousePress(SDL_MouseButtonEvent& b) {
	
	if (b.button == SDL_BUTTON_LEFT) {
		//handle a left-click

		numUnit = 0;
		vSelectedUnit.clear();
		vUnitX.clear();
		vUnitY.clear();

		int x, y;
		SDL_GetMouseState(&x, &y);

		if (x <= 0)
		{
			x = 0;
		}
		else if (x < c.getScreenWidth() && x > 0)
		{
			//Adjust position
			x = (float)x - c.getUnitWidth() / 2;
			//move(timeStep);
		}

		if (y <= 0)
		{
			y = 0;
		}
		else if (y < c.getScreenHeight() && y > 0)
		{
			//Adjust position
			y = (float)y - c.getUnitHeight() / 2;
			//move(timeStep);
		}


		for (size_t i = 0; i < c.getNumUnit(); i++)
		{
			Unit& u = vUnit[i];
			if (u.getSelected())
			{
				numUnit++;
				vSelectedUnit.push_back(i);
			}

		}

		float unitRow = floor(sqrt(numUnit + 2));
		int numRow = numUnit / unitRow ;
		int unitLastRow = numUnit % (int)unitRow;
		printf("Num DOT by floor : %f \n", unitRow);
		printf("Num Row : %d \n", numRow);
		printf("Num dot Last line: %d \n\n", unitLastRow);

		for (size_t i = 0; i < numRow; i++)
		{
			for (size_t j = 0; j < unitRow; j++)
			{
				vUnitX.push_back((float)i * c.getUnitWidth() * 1.5);
				vUnitY.push_back((float)j * c.getUnitHeight() * 1.5);
			}

		}

		//Do the last line if not null
		if (unitLastRow != 0)
		{
			for (size_t i = 0; i < unitLastRow; i++)
			{
				vUnitX.push_back((float)i * c.getUnitWidth() * 1.5);
				vUnitY.push_back((float)unitRow * c.getUnitHeight() * 1.5);
			}
		}

		for (size_t i = 0; i < numUnit; i++)
		{
			Unit& u = vUnit[vSelectedUnit[i]];
			if (u.getSelected())
			{
				u.setUPosToX(x);
				u.setUPosToY(y);

				//u.setUOffsetX(0);
				//u.setUOffsetY(0);
				printf("OffesetUG : X %f|| Y %f\n", vUnitX[i], vUnitY[i]);

				u.setUOffsetX((float)vUnitX[i]);
				u.setUOffsetY((float)vUnitY[i]);
				
				u.isPathFound(false);
			}

		}

	}
}

void UnitGroup::mousePressEnemy(SDL_MouseButtonEvent& b) {
	
	if (b.button == SDL_BUTTON_LEFT) {
		//handle a left-click

		numUnitEnemy = 0;
		vEnemySelectedUnit.clear();
		vEnemyUnitX.clear();
		vEnemyUnitY.clear();

		int x, y;
		SDL_GetMouseState(&x, &y);

		if (x <= 0)
		{
			x = 0;
		}
		else if (x < c.getScreenWidth() && x > 0)
		{
			//Adjust position
			x = (float)x - c.getUnitWidth() / 2;
			//move(timeStep);
		}

		if (y <= 0)
		{
			y = 0;
		}
		else if (y < c.getScreenHeight() && y > 0)
		{
			//Adjust position
			y = (float)y - c.getUnitHeight() / 2;
			//move(timeStep);
		}


		for (size_t i = 0; i < c.getNumUnitEnemy(); i++)
		{
			UnitEnemy& u = vEnemyUnit[i];
			if (u.getSelected() && !u.isUnitDead() && vUnit.size() == 0)
			{
				numUnitEnemy++;
				vEnemySelectedUnit.push_back(i);
			}

		}

		if (numUnitEnemy > 0)
		{
			float unitRow = floor(sqrt(numUnitEnemy + 2));
			int numRow = numUnitEnemy / unitRow ;
			int unitLastRow = numUnitEnemy % (int)unitRow;

			for (size_t i = 0; i < numRow; i++)
			{
				for (size_t j = 0; j < unitRow; j++)
				{
					vEnemyUnitX.push_back((float)i * c.getUnitWidth() * 1.5);
					vEnemyUnitY.push_back((float)j * c.getUnitHeight() * 1.5);
				}

			}

			//Do the last line if not null
			if (unitLastRow != 0)
			{
				for (size_t i = 0; i < unitLastRow; i++)
				{
					vEnemyUnitX.push_back((float)i * c.getUnitWidth() * 1.5);
					vEnemyUnitY.push_back((float)unitRow * c.getUnitHeight() * 1.5);
				}
			}

			for (size_t i = 0; i < numUnit; i++)
			{
				UnitEnemy& u = vEnemyUnit[vEnemySelectedUnit[i]];
				if (u.getSelected())
				{
					u.setUPosToX(x + (float)vEnemyUnitX[i]);
					u.setUPosToY(y + (float)vEnemyUnitY[i]);
				}

			}
		}

	}
}

void UnitGroup::move(float timeStep)
{
	for (size_t i = 0; i < c.getNumUnit(); i++)
	{
		Unit& u = vUnit[i];

		movement.isPathFound(u, u.isPathFound());
		movement.move(u,timeStep);
		u.isPathFound(movement.isPathFound(u));

	}

	//Move Enemy
	//for (size_t i = 0; i < c.getNumUnitEnemy(); i++)
	//{
	//	UnitEnemy& uE = vEnemyUnit[i];
	//	MovementUnit movement = MovementUnit();
	//	movement.moveEnemy(uE,timeStep);
	//}

	startBattle();
}

int UnitGroup::getNumDead()
{
	numUnitDead = 0;

	for (size_t i = 0; i < c.getNumUnit(); i++)
	{
		Unit& u = vUnit[i];

		if (u.isUnitDead())
		{
			numUnitDead++;
		}
	}

	return numUnitDead;
}

int UnitGroup::getNumDeadEnemy()
{
	numUnitEnemyDead = 0;
	for (size_t j = 0; j < c.getNumUnitEnemy(); j++)
	{
		UnitEnemy& uE = vEnemyUnit[j];

		if (uE.isUnitDead())
		{
			numUnitEnemyDead++;
		}
	}

	return numUnitEnemyDead;
}


void UnitGroup::startBattle()
{
	for (size_t i = 0; i < c.getNumUnit(); i++)
	{
		Unit& u = vUnit[i];

		for (size_t j = 0; j < c.getNumUnitEnemy(); j++)
		{
			UnitEnemy& uE = vEnemyUnit[j];

			if (!uE.isUnitDead())
			{
				if (u.checkCollisionEnemy(u.getCollider(), uE.getUPosX(), uE.getUPosY()) || u.checkCollisionEnemy(u.getCollider(), uE.getUPosX() + c.getUnitWidth(), uE.getUPosY()) || u.checkCollisionEnemy(u.getCollider(), uE.getUPosX(), uE.getUPosY() + c.getUnitHeight()) || u.checkCollisionEnemy(u.getCollider(), uE.getUPosX() + c.getUnitWidth(), uE.getUPosY() + c.getUnitHeight()))
				{
					u.attack(uE);
					u.isPathFound(false);
				}
				
			}
		}

	}


}

void UnitGroup::selectUnit(SDL_Rect rect)
{
	SDL_Rect r;
	int x, y, h, w;

	x = rect.x;
	y = rect.y;
	h = rect.h;
	w = rect.w;

	if ( w < 0 )
	{
		x = rect.x + rect.w;
		w = rect.w * -1;
	}

	if ( h < 0)
	{
		y = rect.y + rect.h;
		h = rect.h * -1;
	}

	r.x = x;
	r.y = y;
	r.h = h;
	r.w = w;

	for (size_t i = 0; i < c.getNumUnit(); i++)
	{
		Unit& u = vUnit[i];
		if (u.isInSelection(r) == true)
		{
			u.setSelected(true);
		}
		else
		{
			u.setSelected(false);
		}
	}
}

void UnitGroup::selectUnitEnemy(SDL_Rect rect)
{
	SDL_Rect r;
	int x, y, h, w;

	x = rect.x;
	y = rect.y;
	h = rect.h;
	w = rect.w;

	if (w < 0)
	{
		x = rect.x + rect.w;
		w = rect.w * -1;
	}

	if (h < 0)
	{
		y = rect.y + rect.h;
		h = rect.h * -1;
	}

	r.x = x;
	r.y = y;
	r.h = h;
	r.w = w;

	for (size_t i = 0; i < c.getNumUnitEnemy(); i++)
	{
		UnitEnemy& u = vEnemyUnit[i];
		if (u.isInSelection(r) == true)
		{
			u.setSelected(true);
		}
		else
		{
			u.setSelected(false);
		}
	}
}


