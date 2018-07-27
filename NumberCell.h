#pragma once
#include <vector>

using namespace std;

class NumberCell
{
private:
	int Value;
	int boardRow;
	int boardColumn;
	int blockNumber;
	vector<int> possibleValues;

	void setRow(int b) { boardRow = b; }; // 1-9
	void setColumn(int c) { boardColumn = c; }; // 1-9
	void setBlockNumber(int b) { blockNumber = b; }; // 1-9

public:
	NumberCell(int value, int row, int column, int block);
	~NumberCell();

	void setValue(int v) { Value = v; }; // 0-9
	void setPossibleValues(vector<int> posVal) {possibleValues = posVal; };

	int getValue() { return Value; };
	int getRowNC() { return boardRow; };
	int getColumnNC() { return boardColumn; };
	int getblockNumber() { return blockNumber; };
	vector<int> getPossibleValues() {return possibleValues; };
	string getPossibleValues_str(); // GUI Use

	void printPossibleValues();
};

/*
	A block, row or column is made up of NumberCells. Each NumberCell holds a single number between 0 and 9. A value of zero represents an unset NumberCell, 
	while 1-9 is a set value. The NumberCell has a vector which shows the values this NumberCell can take if it is unset. This vector can be read or written 
	to from outside the NumberCell.

	The NumberCell has no knowledge of the other NumberCells within the row, column and block of which it is a member, hence the possible values vector 
	which will be written to from the NumberBlock and Board classes.
*/

