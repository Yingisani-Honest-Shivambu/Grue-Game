#ifndef LIBZSPACE_H_INCLUDED
#define LIBZSPACE_H_INCLUDED
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <bits/stdc++.h>
using namespace std;
namespace ZorkSpace
{
    struct Game
    {
    //structure (for bonus )
        int intRows = 0;
        int intCols= 0;
        int Numbatteries = 0;
        bool blnContinue = true;
        char Opt = '\0';
        bool blnlights = true;
    };
    //Enumeration
enum Errors
{
    Success = 0,
    Err_Conv = -1,
    Err_Range = -2,
    Err_Argum = -3
};
//constants declaration
const int EMPTY = 0;
const int Player = 1;
const int Pittraps = 2;
const int Batteries = 3;
const char Character[4] = {'.','@','#','O'};
//2D Array declaration
typedef int* oneDArray;
typedef oneDArray* twoDArray;
//function prototypes
int GenR(int intLow,int intHigh);
int Convtoint(string strTemp);
void ValidateArgument(char** argv ,int argc);
twoDArray AllocateAndInit(int Rows,int Cols,int Numbat);
void Placement(twoDArray ArrayC,int ROW,int COL,int AMOUNT,char strCh);
void PrintArray(int introw,int intcol,twoDArray TempArray);
void OutputMenu(int TBFD);
void findplayer(twoDArray TempArray,int row,int col,int& playerR,int& playerC);
void Moveplayer(twoDArray TempArray,int introw,int intcols,char select,int& TurnsB4dawn,bool exit,int& numB);
bool IsintheEnvironment(int rows,int cols,int PR,int PC);
void TorchOff(twoDArray ArrGame,int introw,int intcols);
void MoveplayerinD(twoDArray TempArray,char select,int& TurnsB4dawn,bool exitprogram);
void Deallocate(twoDArray& arraygame,int introws);
}


#endif // LIBZSPACE_H_INCLUDED
