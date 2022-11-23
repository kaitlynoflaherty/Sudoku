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
    ifstream g2;
    ifstream g3;

    // Read in grids from files
    string fileName = "sudoku1.txt";
    string fileName2 = "sudoku2.txt";
    string fileName3 = "sudoku3.txt";

    // Error message if file can't be opened
    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    g2.open(fileName2.c_str());
    if (!g2)
    {
        cerr << "Cannot open " << fileName2 << endl;
        exit(1);
    }

    g3.open(fileName3.c_str());
    if (!g3)
    {
        cerr << "Cannot open " << fileName3 << endl;
        exit(1);
    }

    try
    {
        board b1(SquareSize);

        while (fin && fin.peek() != 'Z')
        {
            // Print original board and conflicts
            b1.initialize(fin);
            b1.print();
            b1.printConflicts();

            // Test for setting a cell
            b1.setCell(1,2,6);
            b1.print();
            b1.printConflicts();

            // Test for clearing a cell
            b1.clearCell(1,2,6);
            b1.print();
            b1.printConflicts();

            // Check if solved
            if (b1.isSolved() == true)
            {
                cout <<"solved"<<endl;
            }
            else
            {
                cout <<"not solved"<<endl;
            }
        }

        board b2(SquareSize);

        while (g2 && g2.peek() != 'Z')
        {
            // Print original board and conflicts
            b2.initialize(g2);
            b2.print();
            b2.printConflicts();

            // Test for setting a cell
            b2.setCell(1,2,6);
            b2.print();
            b2.printConflicts();

            // Test for clearing a cell
            b2.clearCell(1,2,6);
            b2.print();
            b2.printConflicts();

            // Check if solved
            if (b2.isSolved() == true)
            {
                cout <<"solved"<<endl;
            }
            else
            {
                cout <<"not solved"<<endl;
            }
        }

        board b3(SquareSize);

        while (g3 && g3.peek() != 'Z')
        {
            // Print original board and conflicts
            b3.initialize(g3);
            b3.print();
            b3.printConflicts();

            // Test for setting a cell
            b3.setCell(1,2,6);
            b3.print();
            b3.printConflicts();

            // Test for clearing a cell
            b3.clearCell(1,2,6);
            b3.print();
            b3.printConflicts();

            // Check if solved
            if (b3.isSolved() == true)
            {
                cout <<"solved"<<endl;
            }
            else
            {
                cout <<"not solved"<<endl;
            }
        }
    }

    catch  (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
} // end main