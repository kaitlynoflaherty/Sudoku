#ifndef CELL_CLASS
#define CELL_CLASS

#include <vector>
#include <iostream>
using namespace std;

class Cell
// Cell class to define the cell and cell functions
{
    public:
    // constructor 
    Cell();
    Cell(int value);
    
    // member fucntions
    int getCell();
    void setCell(int value);
    vector<int> isPossible;
    vector<int> getConflicts();
    void clearCell();
    void addConflict(int num);
    friend ostream &operator<<(ostream &ostr, const Cell& cell);

    // value in cell from input board file
    bool givenVal;

    private:
    // value of cell and vector containing conflicts
    int _cellValue;
    vector<int> conflicts;

}; // end Cell class


Cell::Cell()
// blank cell constructor
{
    givenVal = false;
}


Cell::Cell(int value)
// contructor for filled cell
{
    givenVal = true;
}


int Cell::getCell()
// Function to get the value of a cell
{
    return _cellValue;
}


void Cell::setCell(int value)
// Function to get cell value
{
    _cellValue = value;
}


void Cell::clearCell()
// Function to reset cell value and clear all conflicts
{
    _cellValue = -1;
    givenVal = false;
    isPossible.clear();
    conflicts.clear();
}


void Cell::addConflict(int num)
// Function to add a conflict to a cell
{
    bool containsNum = false;
    for (int i = 0; i < conflicts.size(); i++)
    {
        if (conflicts[i] == num)
        {
            containsNum = true;
        }
    }
}


vector<int> Cell::getConflicts()
// Function to get the cell conflicts
{
    return conflicts;
}


ostream &operator<<(ostream &ostr, const Cell& cell)
// Overloaded cout operator print cell
{
    ostr << cell._cellValue;
    return ostr;
}


#endif	// End cell class