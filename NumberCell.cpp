#include "NumberCell.h"
#include <string>
#include <iostream>



NumberCell::NumberCell(int v, int r, int c, int b)
{
	Value = v;
	boardRow = r;
	boardColumn = c;
	blockNumber = b;

	if (v > 0)
	{
		possibleValues = vector<int>(1,v);
	}
	else
	{
		possibleValues = vector<int>{1,2,3,4,5,6,7,8,9};
	}
}


NumberCell::~NumberCell()
{
}

string NumberCell::getPossibleValues_str()
{
	string str;

	for (vector<int>::iterator it = possibleValues.begin(); it != possibleValues.end(); it++)
	{
		str.append(to_string(*it));
		str.append(", ");
	}
	
	return str;
}

void NumberCell::printPossibleValues()
{
	string str;

	for (vector<int>::iterator it = possibleValues.begin(); it != possibleValues.end(); it++)
	{
		str.append(to_string(*it));
		str.append(", ");
	}
	cout << str << endl;
}
