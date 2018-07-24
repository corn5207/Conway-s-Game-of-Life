/* Game of Life
 * Developer: Yu-Min Chen
 * Date: 2017/3/4
 */

#include <iostream>
#include <cstring>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <time.h>

using namespace std;

const int MAX_COL = 60;
const int MAX_ROW = 30;

void displayMenu(void);
void setZeroArray(char tempArray[MAX_ROW][MAX_COL]);
void setInitialPatternArray(char currentArray[MAX_ROW][MAX_COL]);
void setFilePatternArray(string fileName, char currentArray[MAX_ROW][MAX_COL]);
void copyArray(char tempArray[MAX_ROW][MAX_COL], char currentArray[MAX_ROW][MAX_COL]);
void displayArray(char currentArray[MAX_ROW][MAX_COL]);
void setNextGenArray(char currentArray[MAX_ROW][MAX_COL], char tempArray[MAX_ROW][MAX_COL]);
void createLiveCell(char currentArray[MAX_ROW][MAX_COL]);
void saveArrayToFile(char currentArray[MAX_ROW][MAX_COL]);

int main()
{
    char ans;
	bool t;
    char currentArray[MAX_ROW][MAX_COL];
    char tempArray[MAX_ROW][MAX_COL];

    setZeroArray(tempArray);
    copyArray(tempArray, currentArray);
    setInitialPatternArray(currentArray);
    displayMenu();
    displayArray(currentArray);

    do
    {
        ans = getch();
        switch (ans)
        {
            case '1':
            {
                string fileName = "pattern1.txt";
                setFilePatternArray(fileName, currentArray);
                break;
            }
            case '2':
            {
                string fileName = "pattern2.txt";
                setFilePatternArray(fileName, currentArray);
                break;
            }
            case '3':
            {
                string fileName = "pattern3.txt";
                setFilePatternArray(fileName, currentArray);
                break;
            }
            case 'C':
            case 'c':
            {
                setZeroArray(tempArray);
                copyArray(tempArray, currentArray);
                break;
            }
            case 'S':
            case 's':
            {
                break;
            }
            case 'T':
            case 't':
            {
                createLiveCell(currentArray);
                break;
            }
            case 'A':
            case 'a':
            {
                saveArrayToFile(currentArray);
                break;
            }
        }
        while (ans == 'p' || ans == 'P')
        {
            if (t = kbhit())
            {
                break;
            }
            else
            {
                system("cls");
                displayMenu();
                setNextGenArray(currentArray, tempArray);
                copyArray(tempArray, currentArray);
                displayArray(currentArray);
                Sleep(300);
            }
        }

    system("cls");
    displayMenu();
    displayArray(currentArray);
    }while ((ans != 'q')&&(ans != 'Q'));

    return 0;
}

void displayMenu(void)
{
    cout << "Press [1], [2], or [3] to load the patterns" << endl;
    cout << "Press [P] to loop the output \t Press [S] to stop the loop" << endl;
    cout << "Press [Q] to exit the program \t Press [C] to clear the pattern" << endl;
    cout << "Press [T] to create a pattern from the user's input" << endl;
    cout << "Press [A] to save the current pattern" << endl << endl;
}

void setZeroArray(char tempArray[MAX_ROW][MAX_COL])
{
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 60; j++)
        {
            tempArray[i][j] = '.';
        }
    }
}

void setInitialPatternArray(char currentArray[MAX_ROW][MAX_COL])
{
    int rowRandom=15;
    int colRandom=30;
    currentArray[rowRandom][colRandom] = 'O';
    for (int i = rowRandom; i < rowRandom + 5; i++)
    {
        currentArray[i][colRandom] = 'O';
        currentArray[i][colRandom+6] = 'O';
    }
    for (int j = colRandom; j < colRandom + 7; j++)
    {
        currentArray[rowRandom+5][j] = 'O';
    }
}

void setFilePatternArray(string fileName, char currentArray[MAX_ROW][MAX_COL])
{
    setZeroArray(currentArray);
    ifstream in_stream;
    in_stream.open(fileName.c_str());

    while (! in_stream.eof())
    {
        int i, j;
        in_stream >> i;
        in_stream >> j;
        currentArray[i][j] = 'O';
    }
    in_stream.close();
}

void copyArray(char tempArray[MAX_ROW][MAX_COL], char currentArray[MAX_ROW][MAX_COL])
{
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 60; j++)
        {
            currentArray[i][j] = tempArray[i][j];
        }
    }
}

void displayArray(char currentArray[MAX_ROW][MAX_COL])
{
     for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 60; j++)
        {
            cout << currentArray[i][j];
        }
        cout << endl;
    }
}

void setNextGenArray(char currentArray[MAX_ROW][MAX_COL], char tempArray[MAX_ROW][MAX_COL])
{
	int neighbors;
    for (int m = 0; m < MAX_ROW; m++)
    {
        for (int n = 0; n < MAX_COL; n++)
        {
            neighbors = 0;

            if ((m == 0) && (n != 0) && (n != (MAX_COL-1))) // first row
            {
                if (currentArray[m][n-1] == 'O') neighbors += 1;
                if (currentArray[m][n+1] == 'O') neighbors += 1;
                if (currentArray[m+1][n-1] == 'O') neighbors += 1;
                if (currentArray[m+1][n] == 'O') neighbors += 1;
                if (currentArray[m+1][n+1] == 'O') neighbors += 1;
            }
            else if (m == (MAX_ROW - 1) && (n != 0) && (n != (MAX_COL-1))) // last row
            {
                if (currentArray[m-1][n-1] == 'O') neighbors += 1;
                if (currentArray[m-1][n] == 'O') neighbors += 1;
                if (currentArray[m-1][n+1] == 'O') neighbors += 1;
                if (currentArray[m][n-1] == 'O') neighbors += 1;
                if (currentArray[m][n+1] == 'O') neighbors += 1;
            }
            else if ((n == 0) && (m != 0) && (m != (MAX_ROW - 1))) // first column
            {
                if (currentArray[m-1][n] == 'O') neighbors += 1;
                if (currentArray[m-1][n+1] == 'O') neighbors += 1;
                if (currentArray[m][n+1] == 'O') neighbors += 1;
                if (currentArray[m+1][n] == 'O') neighbors += 1;
                if (currentArray[m+1][n+1] == 'O') neighbors += 1;
            }
            else if ((n == (MAX_COL-1)) && (m != 0) && (m != (MAX_ROW - 1))) // last column
            {
                if (currentArray[m-1][n-1] == 'O') neighbors += 1;
                if (currentArray[m-1][n] == 'O') neighbors += 1;
                if (currentArray[m][n-1] == 'O') neighbors += 1;
                if (currentArray[m+1][n-1] == 'O') neighbors += 1;
                if (currentArray[m+1][n] == 'O') neighbors += 1;
            }
            else if ((m == 0) && (n == 0))
            {
                if (currentArray[m][n+1] == 'O') neighbors += 1;
                if (currentArray[m+1][n] == 'O') neighbors += 1;
                if (currentArray[m+1][n+1] == 'O') neighbors += 1;
            }
            else if ((m == (MAX_ROW - 1)) && (n == 0))
            {
                if (currentArray[m-1][n] == 'O') neighbors += 1;
                if (currentArray[m-1][n+1] == 'O') neighbors += 1;
                if (currentArray[m][n+1] == 'O') neighbors += 1;
            }
            else if ((m == 0) && (n == (MAX_COL - 1)))
            {
                if (currentArray[m][n-1] == 'O') neighbors += 1;
                if (currentArray[m+1][n-1] == 'O') neighbors += 1;
                if (currentArray[m+1][n] == 'O') neighbors += 1;
            }
            else if ((m == (MAX_ROW - 1)) && (n == (MAX_COL - 1)))
            {
                if (currentArray[m-1][n-1] == 'O') neighbors += 1;
                if (currentArray[m-1][n] == 'O') neighbors += 1;
                if (currentArray[m][n-1] == 'O') neighbors += 1;
            }
            else
            {
                if (currentArray[m-1][n-1] == 'O') neighbors += 1;
                if (currentArray[m-1][n] == 'O') neighbors += 1;
                if (currentArray[m-1][n+1] == 'O') neighbors += 1;
                if (currentArray[m][n-1] == 'O') neighbors += 1;
                if (currentArray[m][n+1] == 'O') neighbors += 1;
                if (currentArray[m+1][n-1] == 'O') neighbors += 1;
                if (currentArray[m+1][n] == 'O') neighbors += 1;
                if (currentArray[m+1][n+1] == 'O') neighbors += 1;
            }

            if (currentArray[m][n] == 'O' && neighbors < 2)
            tempArray[m][n] = '.';
            else if (currentArray[m][n] == 'O' && neighbors > 3)
            tempArray[m][n] = '.';
            else if (currentArray[m][n] == 'O' && (neighbors == 2 || neighbors == 3))
            tempArray[m][n] = 'O';
            else if (currentArray[m][n] == '.' && neighbors == 3)
            tempArray[m][n] = 'O';
        }
    }
}

void createLiveCell(char currentArray[MAX_ROW][MAX_COL])
{
    int row, column;
    string end;
    while (1)
    {
        cout << "Enter a row and column: (press [L] to leave)" << endl;
        cin >> row  ;
        if ( !( cin >> column ) )
        {
            cin.clear();
            getline(cin, end);
            break;
        }
        currentArray[row][column] = 'O';
        system("cls");
        displayMenu();
        displayArray(currentArray);
    }
}

void saveArrayToFile(char currentArray[MAX_ROW][MAX_COL])
{
    ofstream out_stream;
    string fileName;
    cout << "Enter the file name you want to save (ex. pattern4.txt) :" << endl;
    cin >> fileName;
    out_stream.open(fileName.c_str());

    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 60; j++)
        {
            if (currentArray[i][j] == 'O')
            {
                out_stream << i;
                out_stream << endl;
                out_stream << j;
                out_stream << endl;
            }
        }
    }
    out_stream.close();
}
