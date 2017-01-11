#include"Cells.h"

int Cell::neighbourhood(int x, int y)				//calculate number of live neighbours immediately surrounding a cell
{
	return(
		(inBounds(x - 1, y - 1) ? operator()(x - 1, y - 1) : 0)		// a cell could have max 8 neighbours. this function
		+ (inBounds(x - 1, y) ? operator()(x - 1, y) : 0)			// first checks if those neighbours are a valid cell (not outside bounds)
		+ (inBounds(x - 1, y + 1) ? operator()(x - 1, y + 1) : 0)	// If it is, it adds 1 if it's live. else adds 0.
		+ (inBounds(x, y - 1) ? operator()(x, y - 1) : 0)			//
		+ (inBounds(x, y + 1) ? operator()(x, y + 1) : 0)			//
		+ (inBounds(x + 1, y - 1) ? operator()(x + 1, y - 1) : 0)	//
		+ (inBounds(x + 1, y) ? operator()(x + 1, y) : 0)			// The final sum is the number of live neighbors of cell (x,y)
		+ (inBounds(x + 1, y + 1) ? operator()(x + 1, y + 1) : 0)	//
		);
}

void Cell::set(int x, int y, int populationState)	//adds entry in updatelist for changing state of cell (x,y) to "populationState"
{
	_updateList.push_back(x);
	_updateList.push_back(y);
	_updateList.push_back(populationState);
}

void Cell::update()									//actually makes changes in cell map according to update list
{
	for (unsigned int i = 0; i < _updateList.size(); i += 3)	//increments of 3 because i= x-index, i+1= y-index, i+2=populationState.
		_cellMap[_updateList[i]][_updateList[i + 1]] = _updateList[i + 2];
	_updateList.clear();
}

int Cell::inBounds(int x, int y)					//check whether (x,y) is a valid cell inside the grid or not
{
	if (x >= 0 && y >= 0 && x < _gridSize && y < _gridSize)
		return TRUE;
	else
		return FALSE;
}

void Cell::applyRule(int x, int y, rule r)			//apply specific rule 'r' to cell (x,y). Called from ApplyRules()
{
	if (this->operator()(x, y) == r.populationState)
	{
		int c = 0;
		int count = this->neighbourhood(x, y);

		if (count < r.neighbourCount)				// bitwise operations to check the conditions <, > and = between (x,y)'s
			c = c | LESS_THAN;						// neighbor count and the rule's required neighbour count
		if (count == r.neighbourCount)
			c = c | EQUAL_TO;
		if (count > r.neighbourCount)
			c = c | GREATER_THAN;

		if (c & r.conditionType)
			this->set(x, y, r.result);
	}
}

void Cell::Initialize(int size)					//allocates cellmap of size (size X size)
{
	_gridSize = size;
	_cellMap = new int*[size];
	for (int i = 0; i < _gridSize; i++)
		_cellMap[i] = new int[size]();
}

int Cell::GridSize()							//returns grid size of automaton
{
	return _gridSize;
}

int Cell::operator() (int x, int y)				//returns population state of cell (x,y)
{
	if (!_cellMap)	//cellmap not initialized
		return -1;
	else if (inBounds(x, y))
		return _cellMap[x][y];
	else
		return -1;
}

void Cell::Update(int x, int y, int populationState)	//used for IMMEDIATE change to cellmap instead of pushing to update list and updating later.
{
	if (inBounds(x, y))
		_cellMap[x][y] = populationState;
}

void Cell::Invert(int x, int y)							//changes cell (x,y) from live to dead or dead to live.
{
	_cellMap[x][y] = (_cellMap[x][y] == POPULATED) ? UNPOPULATED : POPULATED;
}

void Cell::AddRule(int populationState, int conditionType, int neighbourCount, int result)	//add new rule to _rules
{
	rule r = { populationState,conditionType,neighbourCount,result };
	_rules.push_back(r);
}

void Cell::ApplyRules()									//applies all rules to all cells in cellmap
{
	for (int i = 0; i < _gridSize; i++)
	{
		for (int j = 0; j < _gridSize; j++)
		{
			for (unsigned int k = 0; k < _rules.size(); k++)
				applyRule(i, j, _rules[k]);
		}
	}
	this->update();
}

void Cell::Reset()										//Clears all cells to unpopulated
{
	for (int i = 0; i < _gridSize; i++)
		for (int j = 0; j < _gridSize; j++)
			_cellMap[i][j] = UNPOPULATED;
}

void Cell::ClearRules()								//deletes all rules
{
	_rules.clear();
}

void Cell::CleanUp()								//deallocate and clear rules.
{
	ClearRules();
	if (!_cellMap) return;
	for (int i = 0; i < _gridSize; i++)
		delete[] _cellMap[i];
	delete[] _cellMap;
	_cellMap = NULL;
}