#include <string>
#include <vector>

int ColumnConversion(int c)	// Gives offset of NumberCell in NumberBlock's Cell Vector
{
	switch (c)
	{
	case 1: case 4: case 7:
		return 0;
	case 2: case 5: case 8:
		return 1;
	case 3: case 6: case 9:
		return 2;
	default:
		return 0;
	}
}

int RowConversion(int r) // Gives offset of NumberCell in NumberBlock's Cell Vector
{
	switch (r)
	{
	case 1: case 4: case 7:
		return 0;
	case 2: case 5: case 8:
		return 3;
	case 3: case 6: case 9:
		return 6;
	default:
		return 0;
	}
}


int BlockOffset(int n) //Converts NumberBlock Row/Column to NumberCell Row/Column number. i.e. Block NumberBlock (2,1) Holds Rows 1-3 Columns 4-6
{
	switch (n)
	{
	case 1:
		return 1;
	case 2:
		return 4;
	case 3:
		return 7;
	default:
		return 1;
	}
}

int RowTOBlockIndex(int r) // Get a Block index from a Row Index. i.e. Row 5 = Block 3, 4 & 5
{
	switch (r)
	{
	case 1:	case 2:	case 3:
		return 0;
	case 4: case 5:	case 6:
		return 3;
	case 7:	case 8:	case 9:
		return 6;
	default:
		return 0;
	}
}

int ColumnTOBlockIndex(int c) // Get a Block index from a Column Index. i.e. Column 5 = Block 2 Index 2,5 & 8
{
	switch (c) 
	{
	case 1:	case 2:	case 3:
		return 0;
	case 4: case 5:	case 6:
		return 1;
	case 7:	case 8:	case 9:
		return 2;
	default:
		return 0;
	}
}
