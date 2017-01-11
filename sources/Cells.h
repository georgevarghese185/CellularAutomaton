#ifndef __CELLS_H_INCLUDED
#define __CELLS_H_INCLUDED

#include<vector>

#define TRUE 1
#define FALSE 0
#define POPULATED 1
#define UNPOPULATED 0
#define LESS_THAN 8
#define EQUAL_TO 4
#define GREATER_THAN 1

using namespace std;

class Cell
{
	int **_cellMap, _gridSize;
	vector<int> _updateList;							//temporary list of cells to be updated
	struct rule{ int populationState, conditionType, neighbourCount, result; };		//holds data for one rule
	vector<rule> _rules;								//dynamic list for storing all specified rules.

	int neighbourhood(int x, int y);					//calculate number of live neighbours immediately surrounding a cell
	void set(int x, int y, int populationState);		//adds entry in updatelist for changing state of cell (x,y) to "populationState"
	void update();										//actually make changes in cell map according to update list
	int inBounds(int x, int y);							//check whether (x,y) is a valid cell inside the grid or not
	void applyRule(int x, int y, rule r);				//apply specific rule 'r' to cell (x,y). Called from ApplyRules()

public:
	void Initialize(int size);							//allocates cellmap of size (size X size)
	int GridSize();										//returns grid size of automaton
	int operator() (int x, int y);						//returns population state of cell (x,y)
	void Update(int x, int y, int populationState);		//used for IMMEDIATE change to cellmap instead of pushing to update list and updating later.
	void Invert(int x, int y);							//changes cell (x,y) from live to dead or dead to live.
	void AddRule(int populationState, int conditionType, int neighbourCount, int result);		//add new rule to _rules
	void ApplyRules();									//applies all rules to all cells in cellmap
	void Reset();										//Clears all cells to unpopulated
	void ClearRules();									//deletes all rules
	void CleanUp();										//deallocate and clear rules.
};

#endif