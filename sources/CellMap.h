#pragma once

#include<vector>

#define POPULATED 1
#define UNPOPULATED 0

using namespace std;

extern int GRID_MAX;

class CellMap

{
	int **_cellMap;
	vector<int> _updateList;
public:

	void Initialize(int size);

	int operator() (int x, int y);

	int Neighbourhood(int x, int y);

	void Set(int x, int y, int populationType);

	void Update();

	void Update(int x, int y, int populationState);

	void invert(int x, int y);

	int InBounds(int x, int y);

	~CellMap();
};

extern CellMap CM;
