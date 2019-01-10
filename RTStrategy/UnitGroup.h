#include "Unit.h"

#include <vector>

#pragma once
class UnitGroup
{
public:
	UnitGroup();
	UnitGroup(SDL_Renderer* gRenderer);

	Config c;

	int numUnit;
	int numUnitEnemy;
	int numUnitDead;
	int numUnitEnemyDead;

	std::vector<Unit> vUnit;
	std::vector<int> vSelectedUnit;
	std::vector<float> vUnitX;
	std::vector<float> vUnitY;

	std::vector<Unit> vEnemyUnit;
	std::vector<int> vEnemySelectedUnit;
	std::vector<float> vEnemyUnitX;
	std::vector<float> vEnemyUnitY;

	void handleEvent(SDL_Event& e);

	void handleEventEnemy(SDL_Event& e);

	void load(SDL_Renderer* gRenderer);

	void mousePress(SDL_MouseButtonEvent& b);

	void mousePressEnemy(SDL_MouseButtonEvent & b);

	void move(float timeStep);

	int getNumDead();

	int getNumDeadEnemy();

	void startBattle();

	void selectUnit(SDL_Rect rect);

	void selectUnitEnemy(SDL_Rect rect);

	void render(SDL_Renderer* gRenderer);

	//float calculSquareX(int position, int unitTotal);

	//float calculSquareY(int position, int unitTotal);

};

