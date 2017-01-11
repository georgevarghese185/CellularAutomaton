#pragma once

#include<vector>

#define POPULATED 1
#define UNPOPULATED 0

using namespace std;

extern int GRID_MAX;

class CellMap

{
	int **_cellMap;
	
public:
	vector<int> _updateList;

	void Initialize(int size);

	int operator() (int x, int y);

	int Neighbourhood(int x, int y);

	void Set(int x, int y, int populationType);

	void Update();

	void Update(int x, int y, int populationState);

	void invert(int x, int y);

	int InBounds(int x, int y);

	void Reset();

	void CleanUp();
};

extern CellMap CM;
