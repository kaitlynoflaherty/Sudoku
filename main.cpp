// Project #4: Sudoku Part B
// 
// Group Members: Lisa Byrne, Kaite O'Flaherty, Alek Tunik
//
// Description: Main file for sudoku project. Loads three sudoku boards, prints 
// the original board, and then the solved board.
// 
// Assumptions: Sudoku Boards given are 9 by 9 and are solvable.

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <tuple>
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

    board b1(SquareSize);
    board b2(SquareSize);
    board b3(SquareSize);

    int total = 0;
    int avg = 0;

    // Error message if file can't be opened
    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
    while (fin && fin.peek() != 'Z')
    {
        b1.initialize(fin);
    }

    g2.open(fileName2.c_str());
    if (!g2)
    {
        cerr << "Cannot open " << fileName2 << endl;
        exit(1);
    }
    while (g2 && g2.peek() != 'Z')
    {
        b2.initialize(g2);
    }
    

    g3.open(fileName3.c_str());
    if (!g3)
    {
        cerr << "Cannot open " << fileName3 << endl;
        exit(1);
    }
    while (g3 && g3.peek() != 'Z')
    {
        b3.initialize(g3);
    }

    // Print original boards and solved boards
    cout << "Board 1 unsolved:" << endl;
    b1.print();
    cout << "Board 1 solved:" << endl;
    int countb1 = 0;
    b1.solve(countb1);

    cout << endl << "Board 2 unsolved:" << endl;
    b2.print();
    cout << "Board 2 solved:" << endl;
    int countb2 = 0;
    b2.solve(countb2);

    cout << endl << "Board 3 unsolved:" << endl;
    b3.print();
    cout << "Board 3 solved:" << endl;
    int countb3 = 0;
    b3.solve(countb3);

    total = b1.getRecursions() + b2.getRecursions() + b3.getRecursions();
    cout << endl << "Recursion Data:" << endl;
    cout << "Recursive calls for Board 1: " << b1.getRecursions() << endl;
    cout << "Recursive calls for Board 2: " << b2.getRecursions() << endl;
    cout << "Recursive calls for Board 3: " << b3.getRecursions() << endl;
    cout << "Total recursive calls: " << total << endl;
    avg = total/3;
    cout << "Average number of recursive calls to solve board: " << avg << endl;
    cout << "All done!" << endl;
    return 0;
} // end main