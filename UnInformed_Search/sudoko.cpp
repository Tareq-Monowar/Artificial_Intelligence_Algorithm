#include <iostream>

using namespace std;

const int SIZE = 9;

// Check whether placing num at (row, col) is valid
bool isSafe(int board[SIZE][SIZE], int row, int col, int num)
{
    // Check row
    for (int i = 0; i < SIZE; i++)
    {
        if (board[row][i] == num)
            return false;
    }

    // Check column
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i][col] == num)
            return false;
    }

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[startRow + i][startCol + j] == num)
                return false;
        }
    }

    return true;
}

// Solve Sudoku using Backtracking
bool solveSudoku(int board[SIZE][SIZE])
{
    int row = -1;
    int col = -1;
    bool emptyCell = false;

    // Find an empty cell
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == 0)
            {
                row = i;
                col = j;
                emptyCell = true;
                break;
            }
        }

        if (emptyCell)
            break;
    }

    // No empty cell means puzzle solved
    if (!emptyCell)
        return true;

    // Try numbers 1 to 9
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(board, row, col, num))
        {
            board[row][col] = num;

            if (solveSudoku(board))
                return true;

            // Backtrack
            board[row][col] = 0;
        }
    }

    return false;
}

// Print Sudoku board
void printBoard(int board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    // Predefined Sudoku (0 = Empty Cell)
    int board[SIZE][SIZE] =
    {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},

        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},

        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };

    cout << "Initial Sudoku:\n\n";
    printBoard(board);

    cout << "\nSolved Sudoku:\n\n";

    if (solveSudoku(board))
    {
        printBoard(board);
    }
    else
    {
        cout << "No solution exists." << endl;
    }

    return 0;
}