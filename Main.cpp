#include "SudukoBoard.h"

#include <iostream>

using namespace std;

int main()
{
	SudukoBoard Board("C:\\Users\\Alan\\Desktop\\sud.csv");

	Board.printCellDetails();

	int count = 0;
	while (count <= 1)
	{
		if (!Board.updatePossibleNumbers())
		{
			count++;
		}
		else
		{
			count = 0;
		}
	}

	Board.printSinglePossibleCells();
	
	system("PAUSE");

	return 0;
}