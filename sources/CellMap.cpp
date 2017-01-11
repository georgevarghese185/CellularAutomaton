#include"CellMap.h"
#define TRUE 1
#define FALSE 0

int GRID_MAX;
CellMap CM;

void CellMap::Initialize(int size)
{
	_cellMap = new int*[size];
	for (int i = 0; i < GRID_MAX; i++)
		_cellMap[i] = new int[size]();
}

int CellMap::operator() (int x, int y)
{
	if (InBounds(x, y))
		return _cellMap[x][y];
	else
		return -1;
}

int CellMap::Neighbourhood(int x, int y)
{
	return(
		(InBounds(x - 1, y - 1) ? operator()(x - 1, y - 1) : 0)
		+ (InBounds(x - 1, y) ? operator()(x - 1, y) : 0)
		+ (InBounds(x - 1, y + 1) ? operator()(x - 1, y + 1) : 0)
		+ (InBounds(x, y - 1) ? operator()(x, y - 1) : 0)
		+ (InBounds(x, y + 1) ? operator()(x, y + 1) : 0)
		+ (InBounds(x + 1, y - 1) ? operator()(x + 1, y - 1) : 0)
		+ (InBounds(x + 1, y) ? operator()(x + 1, y) : 0)
		+ (InBounds(x + 1, y + 1) ? operator()(x + 1, y + 1) : 0)
		);
}

void CellMap::Set(int x, int y, int populationType)
{
	_updateList.push_back(x);
	_updateList.push_back(y);
	_updateList.push_back(populationType);
}

void CellMap::Update()
{

	for (int i = 0; i < _updateList.size(); i += 3)
		_cellMap[_updateList[i]][_updateList[i + 1]] = _updateList[i + 2];
	_updateList.clear();
}

void CellMap::Update(int x, int y, int populationState)
{
	if (InBounds(x, y))
		_cellMap[x][y] = populationState;
}

void CellMap::invert(int x, int y)
{
	_cellMap[x][y] = (_cellMap[x][y] == POPULATED) ? UNPOPULATED : POPULATED;
}

int CellMap::InBounds(int x, int y)
{
	if (x >= 0 && y >= 0 && x < GRID_MAX && y < GRID_MAX)
		return TRUE;
	else
		return FALSE;
}

CellMap::~CellMap()
{
	for (int i = 0; i < GRID_MAX; i++)
		delete[] _cellMap[i];
	delete _cellMap;
}