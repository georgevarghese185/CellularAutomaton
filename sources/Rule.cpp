#include"Rule.h"

Rule::Rule(int populationState, int conditionType, int neighbourCount, int result)
{
	_populationState = populationState;
	_neighbourCount = neighbourCount;
	_conditionType = conditionType;
	_result = result;
}

void Rule::AppyRule(int x, int y)
{
	if (CM(x, y) == _populationState)
	{
		int c = 0;
		int count = CM.Neighbourhood(x, y);

		if (count < _neighbourCount)
			c = c | LESS_THAN;
		if (count == _neighbourCount)
			c = c | EQUAL_TO;
		if (count > _neighbourCount)
			c = c | GREATER_THAN;

		if (c == _conditionType)
			CM.Set(x, y, _result);
	}
}