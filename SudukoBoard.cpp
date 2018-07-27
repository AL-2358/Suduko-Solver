#include "SudukoBoard.h"

#include <iostream>


SudukoBoard::SudukoBoard(string fp)
{
	this->loadBoard(fp);
	this->sortedValues = vector<vector<int>>(9, (vector<int>(9, 0)));
	this->sortVectors();

	int r = 1;
	int c = 1;
	int b = 1;
	
	for (int i = 0; i < 9; i++)
	{
		NumberBlock numblock(this->sortedValues[i],b,r,c,this);
		boardBlocks.push_back(numblock);
		
		b++;
		if (c < 3)
		{
			c++;
		}
		else
		{
			c = 1;
			r++;
		}
	}
}

SudukoBoard::~SudukoBoard()
{
}

void SudukoBoard::loadBoard(string fp)
{
	fstream fs;
	fs.open(fp);

	stringstream ss;
	string temp;

	if (fs.is_open())
	{
		while (!fs.eof())
		{
			vector<int> vi;
			int i;
			char c;

			getline(fs, temp);
			if (temp != "")
			{
				ss << temp;

				while (ss >> i)
				{
					ss >> c;
					vi.push_back(i);
				}
				ss.clear();
				this->startValues.push_back(vi);
			}
		}
		fs.close();
	}
}

void SudukoBoard::sortVectors()
{
	/*
	Starts in form, as the CSV is read in
	[ [A] [A] [A] [B] [B] [B] [C] [C] [C] ]
	[ [A] [A] [A] [B] [B] [B] [C] [C] [C] ]
	[ [A] [A] [A] [B] [B] [B] [C] [C] [C] ]
	[ [D] [D] [D] [E] [E] [E] [F] [F] [F] ]
	[ [D] [D] [D] [E] [E] [E] [F] [F] [F] ]
	[ [D] [D] [D] [E] [E] [E] [F] [F] [F] ]
	[ [G] [G] [G] [H] [H] [H] [I] [I] [I] ]
	[ [G] [G] [G] [H] [H] [H] [I] [I] [I] ]
	[ [G] [G] [G] [H] [H] [H] [I] [I] [I] ]

	Ends in form, I want vectors to represent a block
	[ [A] [A] [A] [A] [A] [A] [A] [A] [A] ]
	[ [B] [B] [B] [B] [B] [B] [B] [B] [B] ]
	[ [C] [C] [C] [C] [C] [C] [C] [C] [C] ]
	[ [D] [D] [D] [D] [D] [D] [D] [D] [D] ]
	[ [E] [E] [E] [E] [E] [E] [E] [E] [E] ]
	[ [F] [F] [F] [F] [F] [F] [F] [F] [F] ]
	[ [G] [G] [G] [G] [G] [G] [G] [G] [G] ]
	[ [H] [H] [H] [H] [H] [H] [H] [H] [H] ]
	[ [I] [I] [I] [I] [I] [I] [I] [I] [I] ]
	*/

	int RowSelector = 0, ColSelector = 0; // looping through loaded values

	int RowOffset = 0, ColOffset = 0; // providing offsets for reading loaded values

	int RowPlacer = 0, ColPlacer = 0; // looping through saving vector


	for (; RowOffset <= 6;)
	{
		for (; ColOffset <= 6;)
		{
			for (; RowSelector < 3; RowSelector++)
			{
				for (; ColSelector < 3; ColSelector++)
				{
					this->sortedValues[RowPlacer][ColPlacer] = this->startValues[RowSelector + RowOffset][ColSelector + ColOffset];
					ColPlacer++;
				}
				ColSelector = 0;
			}
			RowSelector = 0;
			ColOffset += 3;
			RowPlacer++;
			ColPlacer = 0;
		}
		ColOffset = 0;
		RowOffset += 3;
	}
}

void SudukoBoard::printSinglePossibleCells()
{
	for (auto it = boardBlocks.begin(); it != boardBlocks.end(); it++)
	{
		(*it).printSinglePosCells();
	}
}

void SudukoBoard::printCellDetails()
{
	vector<NumberBlock>::iterator itBB;

	for (itBB = boardBlocks.begin(); itBB != boardBlocks.end(); itBB++)
	{
		(*itBB).printCellDetails();
	}
}

bool SudukoBoard::updatePossibleNumbers()
{
	vector<NumberBlock>::iterator itBB;

	for  (itBB = boardBlocks.begin(); itBB  != boardBlocks.end(); itBB++)
	{
		if ((*itBB).updatePossibleValues() == true)
		{
			return true;
		}
	}
	return false;
}

vector<NumberCell *>  SudukoBoard::getRowPtrs(int r)
{
	vector<NumberCell *> cell_ptrs;
	cell_ptrs.reserve(9);

	int i = RowTOBlockIndex(r);

	for (int j = 0; j < 3; j++, i++)
	{
		vector<NumberCell *> rows = this->boardBlocks[i].getRowPointers(r);

		cell_ptrs.insert(cell_ptrs.end(), rows.begin(), rows.end());
	}

	return cell_ptrs;
}

vector<NumberCell *>  SudukoBoard::getColumnPtrs(int c)
{
	vector<NumberCell *> cell_ptrs;
	cell_ptrs.reserve(9);

	int i = ColumnTOBlockIndex(c);

	for (int j = 0; j < 3; j++, i += 3)
	{
		vector<NumberCell *> cols = this->boardBlocks[i].getColPointers(c);

		cell_ptrs.insert(cell_ptrs.end(), cols.begin(), cols.end());
	}

	return cell_ptrs;
}

/*
	Need to update possible values based on rows and cols.
	Options
		* Run process for all cells, or a particular row or col.
	How
		* For a single row 
		* Update date a row or col by taking a row or col number in, calculate for all cells in that row or col
		*
void SudukoBoard::findOccurances()
{
this->numberOccurances = vector<int>(10, 0);

for (vector<NumberBlock>::iterator it = this->boardBlocks.begin(); it != this->boardBlocks.end(); it++)
{
for (int i = 1; i < 10; i++)
{
float result = it->numberPresent_Block(i);

if (result > 0.0)
{
this->numberOccurances[i] = this->numberOccurances[i] + 1;
}
else
{
this->numberOccurances[9] = this->numberOccurances[9] + 1;
}
}
}
}


void SudukoBoard::selectNextNumber()
{
// got vector of ints, index number corresponds to the number it represents

// need to find the highest value that is less than 9
int initialNumber = currentNumber;

for (int i = 1; i < 10; i++)
{
if (numberOccurances[i] < 9)
{
if (numberOccurances[this->currentNumber] < numberOccurances[i])
{
currentNumber = i;
}
}
}

if (initialNumber == currentNumber)
{
srand(time(NULL));
currentNumber = rand() % 9 + 1;
}
}
void SudukoBoard::mapAdjacentBlocks()
{
for (vector<NumberBlock>::iterator it = this->boardBlocks.begin(); it != this->boardBlocks.end(); it++)

int col = it->getBoardColumn();
int row = it->getBoardRow();

for (vector<NumberBlock>::iterator jt = this->boardBlocks.begin(); jt != this->boardBlocks.end(); jt++)
{
if (it != jt)
{
if ((jt->getBoardColumn() == col) || (jt->getBoardRow() == row))
{
it->addAdjacentBlock(&*jt);
}
}
}
cout << it->numberPresent_Block(1) << endl;
}
}
*/
