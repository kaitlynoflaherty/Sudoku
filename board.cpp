// Declarations and functions for project #4

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include "Cell.h"
#include <list>
#include <fstream>

using namespace std;

typedef int Cell; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank

const int SquareSize = 3;  //  The number of cells in a small square
                           //  (usually 3).  The board has
                           //  SquareSize^2 rows and SquareSize^2
                           //  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

int numSolutions = 0;

class board
// Stores the entire Sudoku board
{
   public:
      board(int sqSize);
      void clear();
      void initialize(ifstream &fin);
      void print();
      bool isBlank(int i, int j);
      Cell getCell(int i, int j);

      // ***4a Functions***
      void setCell(int i, int j, int value);
      void emptyCell(int i, int j);
      bool isSolved();
      void setConflicts(int row, int col, Cell &cell);
      void updateConflicts();
      void printConflicts();
      
   private:

      // The following matrices go from 1 to BoardSize in each
      // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)
      matrix<Cell> value;

}; // end board class


board::board(int sqSize)
   : value(BoardSize+1,BoardSize+1)
// Board constructor
{
   clear();
}

void board::clear()
// Mark all possible values as legal for each board entry
{
   for (int i = 1; i <= BoardSize; i++)
      for (int j = 1; j <= BoardSize; j++)
      {
         value[i][j] = Blank;
      }
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
   char ch;

   clear();
   
   for (int i = 1; i <= BoardSize; i++)
      for (int j = 1; j <= BoardSize; j++)
	    {
	       fin >> ch;

          // If the read char is not Blank
	      if (ch != '.')
             setCell(i,j,ch-'0');   // Convert char to int
             value[i][j].givenVal = true;
        }
}

int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
   // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
   // coordinates of the square that i,j is in.  

   return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
   for (int i = 0; i < v.size(); i++)
      ostr << v[i] << " ";
   cout << endl;
}

Cell board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
   if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
      return value[i][j];
   else
      throw rangeError("bad value in getCell");
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad value in setCell");

   return (getCell(i,j) == Blank);
}

void board::print()
// Prints the current board.
{
   for (int i = 1; i <= BoardSize; i++)
   {
      if ((i-1) % SquareSize == 0)
      {
         cout << " -";
	 for (int j = 1; j <= BoardSize; j++)
	    cout << "---";
         cout << "-";
	 cout << endl;
      }
      for (int j = 1; j <= BoardSize; j++)
      {
	 if ((j-1) % SquareSize == 0)
	    cout << "|";
	 if (!isBlank(i,j))
	    cout << " " << getCell(i,j) << " ";
	 else
	    cout << "   ";
      }
      cout << "|";
      cout << endl;
   }

   cout << " -";
   for (int j = 1; j <= BoardSize; j++)
      cout << "---";
   cout << "-";
   cout << endl;
}

void board::setCell(int i, int j, int value)
// Functions to set cell object to matrix value
{
   value[i][j].setCellVal(value);
}

void board::emptyCell(int i, int j)
// Fucntion to clear cell
{
    value[i][j].clearCell();
    updateConflicts();
}

bool board::isSolved()
// Fucntion to determine if solved
{
    bool solved = true;
    updateConflicts();
    int sqr = 0;
    for (int i=0; i<BoardSize; i++)
    {
        for (int j=0; j<BoardSize; j++)
        {
            // check for blanks
            if (isBlank(i, j) == true)
            {
                solved = false;
            }

            //check for conflicts
            sqr = (j+2)/3 + ((i-1)/3)*3;
            if (r_confs[i][j] || c_confs[i][j] || sqr_confs[sqr][j])
            {
               solved = false;
            }
        }
    }
    return solved;
}

int main()
{
   ifstream fin;
   
   // Read the sample grid from the file.
   string fileName = "sudoku.txt";

   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try
   {
      board b1(SquareSize);

      while (fin && fin.peek() != 'Z')
      {
	 b1.initialize(fin);
	 b1.print();
	 b1.printConflicts();
      }
   }
   catch  (indexRangeError &ex)
   {
      cout << ex.what() << endl;
      exit(1);
   }
}
