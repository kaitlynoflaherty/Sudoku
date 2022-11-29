// Declarations and functions for project #4

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <tuple>
#include "d_matrix.h"
#include "d_except.h"

using namespace std;

typedef int ValueType; // The type of the value in a cell
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
      board(int);
      void clear();
      void initialize(ifstream &fin);
      void print();
      bool isBlank(int, int);
      ValueType getCell(int, int);

      // 4a Functions
      void setCell(int, int, int);
      void clearCell(int, int, int);
      void updateConflicts(int, int, int, bool);
      void printConflicts();
      bool isSolved();

      // 4b functions
      bool isLegal(int, int, int);
      bool nextCell(int &, int &);
      bool solve();
      
   private:

      // The following matrices go from 1 to BoardSize in each
      // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)

      matrix<ValueType> value;

      // 4a matrices
      // Keeps track of the conflicts in each row, column, and square
      matrix<bool> r_confs;
      matrix<bool> c_confs;
      matrix<bool> sqr_confs;
      // Keeps track of the digits that have been placed
      matrix<vector<bool> > placed;
};

board::board(int sqSize)
   : value(BoardSize+1,BoardSize+1), r_confs(BoardSize+1,BoardSize+1),
   c_confs(BoardSize+1,BoardSize+1), sqr_confs(BoardSize+1,BoardSize+1),
   placed(BoardSize+1,BoardSize+1)
// Board constructor
// Initializes the size of the 2D board value matrix, 2D conflict matrices,
// and the 3D matrix to track digits that have been placed
{
   clear();
}

void board::clear()
// Mark all possible values as legal for each board entry
{
   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
      {
         for  (int v = 0; v <= BoardSize; v++) // one extra to go from 1 - 9
         {
            placed[i][j].push_back(false);
            value[i][j] = Blank;
            r_confs[i][j] = false;
            c_confs[i][j] = false;
            sqr_confs[i][j] = false;
         }
      }
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

ValueType board::getCell(int i, int j)
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

void board::updateConflicts(int i, int j, int val, bool conf)
// Updates the conflicts lists with a true or false value
{
   r_confs[i][val] = conf;
   c_confs[j][val] = conf;
   int sqr = (j+2)/3 + ((i-1)/3)*3; // equation to find square
   sqr_confs[sqr][val] = conf;
}

void board::setCell(int i, int j, int val)
// Stores a value in a cell and updates conflicts
{
   value[i][j] = val;
   updateConflicts(i, j, val, true);
   placed[i][j][val] = true;
} 

void board::clearCell(int i, int j, int val)
// Clears cell and updates conflicts
{
   value[i][j] = Blank;
   updateConflicts(i, j, val, false);
   placed[i][j][val] = false;
}

bool board::isSolved()
// Fucntion to determine if solved
{
   for (int i=1; i<=BoardSize; i++)
   {
      for (int j=1; j<=BoardSize; j++)
      {
         if (isBlank(i, j))
            return true;
      }
   }
   return false;
}

void board::printConflicts()
// Prints the candidates for each cell
{
   int sqr = 0;
   for (int i = 1; i <= BoardSize; i++)
   {
      for (int j = 1; j <= BoardSize; j++)
      {
         cout << "Cell (" << i << ", " << j << ") candidates: ";
         for (int v = 1; v <= BoardSize; v++)
         {
            sqr = (j+2)/3 + ((i-1)/3)*3;
            if(isBlank(i,j) and !(r_confs[i][v] or c_confs[j][v] or 
               sqr_confs[sqr][v]) and !placed[i][j][v])// J is candidate value
               cout << v << "  ";
         }
         cout << endl;
      }
   }
} // End printConflicts


bool board::isLegal(int i, int j, int v)
// Function to check if a given digit (v) can be placed in a given cell (i, j)
{
   int sqr = (j+2)/3 + ((i-1)/3)*3; // equation to find square
   // legal iff the value hasn't been tried yet and there are no conflicts
   if (!placed[i][j][v] and isBlank(i,j) and !(r_confs[i][v] or c_confs[j][v] or sqr_confs[sqr][v]))
      return true;
   else
      return false;     
} // End isLegal


bool board::nextCell(int &i, int &j)
// Find next cell
{
   // check each cell (i, j) for number of conflicts
   for (i = 1; i <= BoardSize; i++)
   {
      for (j = 1; j <= BoardSize; j++)
      {
         if(isBlank(i,j))
            return true;
      }
   }
   return false;
} // End nextCell


bool board::solve()
// Function that ties together all functions to solve sudoku board
{
   int row = 0;
   int col = 0;
   if(!nextCell(row, col))
   {
      print();
      return true;
   }
   else
   {
      for (int v = 1; v <= BoardSize; v++)
      {
         if(isLegal(row, col, v))
         {
            setCell(row, col, v);
            if(solve())
            {
               return true;
            }
            clearCell(row, col, v);
         }
      }
   }
}