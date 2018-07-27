/*	<</ Brief />>
	
	The SudukoBoard contains a vector of NumberBlocks, each of which hold a vector of NumberCells giving the game board.
	The SudukoBoard add to the functionality of the NumberCells by allowing cells are member.
*/
#pragma once

#include "NumberBlock.h"

#include <vector>
#include <fstream>
#include <sstream>

using namespace std; 

int RowTOBlockIndex(int r);
int ColumnTOBlockIndex(int c);

class SudukoBoard
{
private:
	vector<NumberBlock> boardBlocks;
	vector<vector<int>> startValues;
	vector<vector<int>> sortedValues;

public:
	SudukoBoard(string fp);
	~SudukoBoard();

	void loadBoard(string fp);
	void sortVectors();

	bool updatePossibleNumbers();
	void printSinglePossibleCells();	// Command Line Only
	void printCellDetails();	// Command Line Only

	vector<NumberCell *> getRowPtrs(int r);
	vector<NumberCell *> getColumnPtrs(int c);
};
