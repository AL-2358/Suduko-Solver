#include "SudukoBoard.h"
#include "NumberBlock.h"
#include <math.h>



NumberBlock::NumberBlock(vector<int> numbers, int n, int r, int c, SudukoBoard * ptr)
{
	blockNumber = n;
	boardRow = r;
	boardColumn = c;
	Board_ptr = ptr;

	int r_offset = BlockOffset(r);
	int c_offset = BlockOffset(c);

	for (int i = 0, k = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++, k++)
		{
			NumberCell cell(numbers[k], (r_offset + i), (c_offset + j), n);
			blockCells.push_back(cell);
		}
	}
}

NumberBlock::~NumberBlock()
{
}

vector<NumberCell*> NumberBlock::getRowPointers(int r)
{
	int r_offset = RowConversion(r);

	vector<NumberCell *> returnvec;

	for (int i = 0; i < 3; i++)
	{
		returnvec.push_back(&(this->blockCells[r_offset + i]));
	}
	return returnvec;
}

vector<NumberCell*> NumberBlock::getColPointers(int c)
{
	vector<NumberCell *> returnvec;

	int index = ColumnConversion(c);

	for (int i = 0; i < 9; i += 3)
	{
		returnvec.push_back(&(this->blockCells[index + i]));
	}
	return returnvec;

}

void NumberBlock::printCellDetails()
{
	for (auto it = blockCells.begin(); it != blockCells.end(); it++)
	{
		cout << "Value: " << it->getValue()
			<< "\tRow: " << it->getRowNC()
			<< "\tColumn: " << it->getColumnNC()
			<< "\tBlock: " << it->getblockNumber()
			<< endl;
	}
	cout << endl;
}

void NumberBlock::printSinglePosCells()
{
	for (auto it = blockCells.begin() ; it != blockCells.end(); it++)
	{
		if ((it->getPossibleValues()).size() == 1)
		{
			if (it->getValue() == 0)
			{
				cout << "SINGLE POSSIBLE CELL FOUND " << endl;
			}
		}
	}
}

bool NumberBlock::updatePossibleValues()
{
	vector<NumberCell>::iterator itNC;

	vector<int> blockValues;
	vector<int>::iterator itBV;

	vector<NumberCell *> zeroCells;
	vector<NumberCell *>::iterator itZC;

	cout << "\n\nWorking on Block: " << this->blockNumber << endl;

	for (itNC = this->blockCells.begin(); itNC != this->blockCells.end(); itNC++)
	{

		int val = (*itNC).getValue();
		if (val > 0)
		{
			blockValues.push_back(val);
			(*itNC).setPossibleValues(vector<int>(1,val));
		}
		else
		{
			zeroCells.push_back(&(*itNC));
		}
	}

	cout << zeroCells.size() << " cells with zero value." << endl;

	for (itZC = zeroCells.begin(); itZC != zeroCells.end(); itZC++)
	{
		updatePossibleValuesBlock(*itZC, blockValues);
		updatePossibleValuesRow(*itZC);
		updatePossibleValuesCol(*itZC);

		cout << "Possible Values " << ((*itZC)->getPossibleValues()).size() << "\t Values ";
		
		(*itZC)->printPossibleValues();

		if (((*itZC)->getPossibleValues()).size() == 1)
		{
			cout << "Value Set. Row: " << (*itZC)->getRowNC() << "  Column: " << (*itZC)->getColumnNC() << endl;
			(*itZC)->setValue(((*itZC)->getPossibleValues())[0]);
			return true;
		}
	}
	return false;
}

void NumberBlock::updatePossibleValuesBlock(NumberCell * cell, vector<int> blockValues) 
{
	vector<int> localPosValues;
	vector<int>::iterator itlPV;
	vector<int>::iterator itBV;
	vector<int> newPosValues;
	bool checker = false;

	localPosValues = cell->getPossibleValues();

	for (itlPV = localPosValues.begin(); itlPV != localPosValues.end(); itlPV++)
	{
		for (itBV = blockValues.begin(); itBV != blockValues.end(); itBV++)
		{
			if (*itBV == *itlPV)
			{
				checker = true;
			}
		}
		if (checker == false)
		{
			newPosValues.push_back(*itlPV);
		}
		checker = false;

	}
	cell->setPossibleValues(newPosValues); // want the cell in the block to be updated not the zero cells 
	newPosValues.clear();
}

void NumberBlock::updatePossibleValuesRow(NumberCell * cell)
{
	vector<int> rowValues;
	vector<int> localPosValues;
	vector<int> newPosValues;
	vector<NumberCell *> zeroCells;

	bool checker = false;

	int row = cell->getRowNC();

	vector<NumberCell *> cell_ptrs = Board_ptr->getRowPtrs(row); // DOESNT RETURN THE CORRECT ROW PTRS

	for (vector<NumberCell *>::iterator it = cell_ptrs.begin(); it != cell_ptrs.end(); it++)
	{
		int val = (*it)->getValue();

		if (val > 0)
		{
			rowValues.push_back(val);
		}
		else
		{
			zeroCells.push_back(*it);
		}
	}
	
	for (vector<NumberCell *>::iterator it = zeroCells.begin(); it != zeroCells.end(); it++)
	{
		localPosValues = (*it)->getPossibleValues();

		for (vector<int>::iterator it_two = localPosValues.begin(); it_two != localPosValues.end(); it_two++)
		{
			for (vector<int>::iterator it_three = rowValues.begin(); it_three != rowValues.end(); it_three++)
			{
				if (*it_two == *it_three)
				{
					checker = true;
				}
			}
			if (checker == false)
			{
				newPosValues.push_back(*it_two);
			}
			checker = false;
		}
		(*it)->setPossibleValues(newPosValues);
		newPosValues.clear();
	}
}

void NumberBlock::updatePossibleValuesCol(NumberCell * cell)
{
	vector<int> colValues;
	vector<int> localPosValues;
	vector<int> newPosValues;
	vector<NumberCell *> zeroCells;

	bool checker = false;

	int  col = cell->getColumnNC();

	vector<NumberCell *> cell_ptrs = Board_ptr->getColumnPtrs(col);

	for (vector<NumberCell *>::iterator it = cell_ptrs.begin(); it != cell_ptrs.end(); it++)
	{
		int val = (*it)->getValue();

		if (val > 0)
		{
			colValues.push_back(val);
		}
		else
		{
			zeroCells.push_back(*it);
		}
	}

	for (vector<NumberCell *>::iterator it = zeroCells.begin(); it != zeroCells.end(); it++)
	{
		localPosValues = (*it)->getPossibleValues();

		for (vector<int>::iterator it_two = localPosValues.begin(); it_two != localPosValues.end(); it_two++)
		{
			for (vector<int>::iterator it_three = colValues.begin(); it_three != colValues.end(); it_three++)
			{
				if (*it_two == *it_three)
				{
					checker = true;
				}
			}
			if (checker == false)
			{
				newPosValues.push_back(*it_two);
			}
			checker = false;
		}
		(*it)->setPossibleValues(newPosValues);
		newPosValues.clear();
	}
}
