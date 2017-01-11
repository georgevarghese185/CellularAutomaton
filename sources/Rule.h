#pragma once

#include"CellMap.h"

#define LESS_THAN 8
#define EQUAL_TO 4
#define NOT_EQUAL_TO 2
#define GREATER_THAN 1

class Rule
{
	int _populationState, _conditionType, _neighbourCount, _result;

public:
	Rule(int populationState, int conditionType, int neighbourCount, int result);

	void AppyRule(int x, int y);
};
