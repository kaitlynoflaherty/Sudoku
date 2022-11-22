// Project #4: Sudoku Part A
// 
// Group Members: Lisa Byrne, Kaite O'Flaherty, Alek Tunik
//
// Description: Main file for sudoku project.

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "cell.h"
#include "d_matrix.h"
#include "d_except.h"
#include "board.h"


using namespace std;

int main()
{
    ifstream fin;

    // Read the sample grid from the file.
    string fileName = "sudoku1.txt";

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
} // end main