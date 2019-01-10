#define X_MAX 1000
#define X_STEP 100
#define Y_MAX 800
#define Y_STEP 80

#include <vector>
#include <iostream>

#include "TilesArray.h"

#pragma once

struct Node
{
	int y;
	int x;
	int parentX;
	int parentY;
	float gCost;
	float hCost;
	float fCost;
};

inline bool operator < (const Node& lhs, const Node& rhs)
{//We need to overload "<" to put our struct into a set
	return lhs.fCost < rhs.fCost;
}

class APathFinding
{
public:
	APathFinding();
	~APathFinding();

	static TilesArray ta;

	static bool isValid(int x, int y);

	//static bool isDestination(int x, int y, Node dest);
};

