/*	<</ Brief />>
	
	The NumberBlock holds a vector of NumberCells and location information to identify it's posistion on the board and therefor other blocks relevant it itself.
	The NumberBlock can retrieve pointers too a row or column of three NumberCells's contained within its vector. It can also check to see if a number is present
	within the block. 

	The NumberBlock can update the 'posibleValues' vector of all the NumberCells within the NumberBlock, but cannot take into account the row or cols which those
	cells are member.																	*/


#pragma once

#include "NumberCell.h"

#include <vector>
#include <iostream>

using namespace std;

class SudukoBoard;
int ColumnConversion(int c);
int RowConversion(int r);
int BlockOffset(int n);

class NumberBlock
{
private: 
	int blockNumber;
	int boardRow;
	int boardColumn;
	vector<NumberCell> blockCells;
	SudukoBoard * Board_ptr;

public:
	NumberBlock(vector<int> numbers, int n, int r, int c, SudukoBoard * ptr);
	~NumberBlock();

	int getBoardRow() { return boardRow; };
	int getBoardColumn() { return boardColumn; };

	vector<NumberCell *> getRowPointers(int r);
	vector<NumberCell *> getColPointers(int c);

	void printCellDetails();
	void printSinglePosCells();

	bool updatePossibleValues();
	void updatePossibleValuesBlock(NumberCell * cell, vector<int> blockValues);
	void updatePossibleValuesRow(NumberCell * cell);
	void updatePossibleValuesCol(NumberCell * cell);
};


/*	void updatePossibleValues(); ::Update possible values vector for all cells
	1: iterate through all cells and find the numbers present in the block. store these numbers in a vector 'blockvalues'
	2: need to then iterate through all the cells. find the unset cells (valued at zero)
	3: for the zero'd cells get the possible values vector store it locally.
	4: iterate through that vector and remove values that are present in the 'blockvalues' vector
		A: vector of possible values
		B: vector of block values
		C: iterate through possible values, for each step iterate through block values and compare, if equal erase that value from possible values and
		   break loop
	5: once possible values for that cell has been exhausted set the NumberCells possible values to equal the cut local possible values vector.		*/

/* POSSIBLE REMOVAL
private:

void addAdjacentBlock(NumberBlock * ab);
vector<NumberBlock*> adjacentBlocks;																*/

