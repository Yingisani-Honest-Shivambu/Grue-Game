#include "libZspace.h"

namespace ZorkSpace
{
    //function generating random numbers
   int GenR(int intLow,int intHigh)
    {
        int intRange = intHigh-intLow +1;
            return rand()%intRange + intLow;
    }
    //convertion of a string to an integer
int Convtoint(string strTemp)
{
    int intNum = 0;
    stringstream ss {strTemp};
    ss >> intNum;
    if (ss.fail())
    {
        cerr <<  "Couldnt convert to integer! \n";
        exit(Err_Conv);

    }
    return intNum;
}
//vallidating Arguments
void ValidateArgument(char** argv ,int argc)
{
    if (argc != 4)
    {
        cerr << "Invalid number of arguments!" << endl;
        cerr <<"Run the program with " << argv[0] << " <Total number of rows> <Total Number of cols> <Total number of batteries \n";
        exit(Err_Argum);
    }
}
//memory Allocation and Initiallisation
twoDArray AllocateAndInit(int Rows,int Cols,int Numbat)
{
    //memory Allocation
   twoDArray Arr1 = new oneDArray[Rows];
   for (int r = 0;r <Rows;r++)
   {
       Arr1[r] = new int[Cols];
       //initialising everything in the Array to "."
       for (int c = 0 ; c<Cols ;c++)
       {
           Arr1[r][c] = 0 ;
       }
   }
   int Numpittrap =0;
Numpittrap = 0.15*(Rows*Cols);
   Placement(Arr1,Rows,Cols,Numpittrap,Pittraps);
   Placement(Arr1,Rows,Cols,1,Player);
   Placement(Arr1,Rows,Cols,Numbat,Batteries);
   return Arr1;
}
//Display Environment
void PrintArray(int introw,int intcol,twoDArray TempArray)
{
    cout << "      Hint:#-pittraps, O-Batteries, @-Player \n"<<endl;
for (int r=0 ;r < introw;r++)
{
    for (int c = 0;c < intcol;c++)
    {
        int f = TempArray[r][c];
        cout << Character[f] << "  ";
    }
    cout << endl;
    cout <<endl;
}


}
//finding current player location
void findplayer(twoDArray TempArray,int row,int col,int& playerR,int& playerC)
{
    for (int r = 0;r < row;r++)
    {
        for (int c=0;c<col;c++)
        {
            if (TempArray[r][c] == Player)
            {
                playerR = r;
                playerC = c;
            }
        }
    }
}
//Environment check function
bool IsintheEnvironment(int rows,int cols,int PR,int PC)
{
    return (PR >= 0 && PR < rows && PC >= 0 && PC < cols);
}
//movement of player function
void Moveplayer(twoDArray TempArray,int introw,int intcols,char select,int& TurnsB4dawn,bool exitprogram,int& numB)
{
    exitprogram = true;
    int playerRowPosition = 0;
    int playerColPosition = 0;
    findplayer(TempArray,introw,intcols,playerRowPosition,playerColPosition);
   int DestRow = playerRowPosition;
   int DestCol = playerColPosition;


    if (IsintheEnvironment(introw,intcols,playerRowPosition,playerColPosition))
    {
          switch(select)
    {
        case 'W':
            {
                DestRow--;
                break;
            }
        case 'S':
            {
                DestRow++;
                break;
            }
        case 'A':
            {
                DestCol--;
                break;
            }
        case 'D':
            {
                 DestCol++;
                 break;
            }

    }
    }
  if(IsintheEnvironment(introw,intcols,DestRow,DestCol))
  {
      if (TempArray[DestRow][DestCol] == Batteries)
      {
           numB--;
           TurnsB4dawn--;
           TempArray[DestRow][DestCol] = Player;
           TurnsB4dawn += 3;
      }else if (TempArray[DestRow][DestCol] == Pittraps)
      {
          TempArray[DestRow][DestCol] = Player;
          system("cls");
          cout << " YOU FELL INSIDE A PITTRAP!" <<endl;
          cout << " -----------------------------------\n"
          << "|                                  |\n"
          << "|      ****  GAME OVER  ****       |\n"
          << " -----------------------------------\n";
          exitprogram = false;
          exit(0);
      }
      else{
           TurnsB4dawn--;
           TempArray[DestRow][DestCol] += Player;
      }
      TempArray[playerRowPosition][playerColPosition] -= Player;
      if (TurnsB4dawn == 0)
      {
          system("cls");
          cout << " YOU RAN OUT OF BATTERIES FOR MOVEMENTS BEFORE DAWN!" <<endl;
          cout << " -----------------------------------\n"
          << "|                                  |\n"
          << "|      ****  GAME OVER  ****       |\n"
          << " -----------------------------------\n";
          exitprogram = false;
          exit(0);
      }else if (numB <=0)
      {
           system("cls");
          cout << "  Congradulations!!! You have collected enough batteries before dawn" <<endl;
          cout << " -----------------------------------\n"
          << "|                                  |\n"
          << "|      *****  YOU WON  *****       |\n"
          << " -----------------------------------\n";
          exitprogram = false;
          exit(0);
      }
  }

}
//menu function
void OutputMenu(int TBFD)
{
      cout << "         Movements of player: \n"
         << "W-Up/north \n"
         << "S-Down/South \n"
         << "A-Left/West \n"
         << "D-Right/East \n"
         << "O-Switch torch off \n"
         << "T-Switch ON Torch\n"
         << "Q-Quit \n"
         << "Number of turns left before Dawn: " <<  TBFD << endl;
}
//placing characters function
void Placement(twoDArray ArrayC,int ROW,int COL,int AMOUNT,char strCh)
{
    for (int track = 0;track < AMOUNT;track++)
    {
        int r = GenR(0,ROW-1);
        int c = GenR(0,COL-1);
        while(ArrayC[r][c] != EMPTY)
        {
            r=GenR(0,ROW-1);
            c=GenR(0,COL-1);
        }
        ArrayC[r][c] = strCh;
    }
}
//Displaying 1 radius environment since the torch is off
void TorchOff(twoDArray ArrGame,int introw,int intcols)
{

    int playerRowPosition = 0;
    int playerColPosition = 0;
    findplayer(ArrGame,introw,intcols,playerRowPosition,playerColPosition);
   int DestRow = playerRowPosition;
   int DestCol = playerColPosition;


for (int r = DestRow-1;r < DestRow+2;r++)
    {
        for (int c=DestCol-1;c<DestCol+2;c++)
        {
            if (c < 0 || c >= intcols)
            {

            }else if (r < 0 || r >=introw )
            {

            }
           else
            {
            int f = ArrGame[r][c];
                  cout << Character[f] << "  ";
            }

        }
        cout <<endl;
        cout <<endl;
    }
}
//moving the play while in a dark place
void MoveplayerinD(twoDArray TempArray,char select,int& TurnsB4dawn,bool exitprogram)
{
exitprogram = true;
int playerColPosition = 0;
int playerRowPosition = 0;
 for (int r = 0;r < 3;r++)
    {
        for (int c=0;c<3;c++)
        {
            if (TempArray[r][c] == Player)
            {
                playerRowPosition = r;
                playerColPosition = c;
            }
        }
    }
    int DestRow = playerRowPosition;
    int DestCol = playerColPosition;

    if (IsintheEnvironment(3,3,DestRow,DestCol))
    {
          switch(select)
    {
        case 'W':
            {
                DestRow--;
                break;
            }
        case 'S':
            {
                DestRow++;
                break;
            }
        case 'A':
            {
                DestCol--;
                break;
            }
        case 'D':
            {
                 DestCol++;
                 break;
            }

    }
    }
  if(IsintheEnvironment(3,3,DestRow,DestCol))
  {
      if (TempArray[DestRow][DestCol] == Batteries)
      {
           TurnsB4dawn--;
           TempArray[DestRow][DestCol] = Player;
           TurnsB4dawn += 3;
      }else if (TempArray[DestRow][DestCol] == Pittraps)
      {
          TempArray[DestRow][DestCol] = Player;
          system("cls");
          cout << " YOU FELL INSIDE A PITTRAP!" <<endl;
          cout << " -----------------------------------\n"
          << "|                                  |\n"
          << "|      ****  GAME OVER  ****       |\n"
          << " -----------------------------------\n";
          exitprogram = false;
          exit(0);
      }
      else{
           TurnsB4dawn--;
           TempArray[DestRow][DestCol] += Player;
      }
      TempArray[playerRowPosition][playerColPosition] -= Player;
      if (TurnsB4dawn == 0)
      {
          system("cls");
          cout << " YOU RAN OUT OF BATTERIES FOR MOVEMENTS!" <<endl;
          cout << " -----------------------------------\n"
          << "|                                  |\n"
          << "|      ****  GAME OVER  ****       |\n"
          << " -----------------------------------\n";
          exitprogram = false;
          exit(0);
      }
  }
}
//memory deallocation
void Deallocate(twoDArray& arraygame,int introws)
{
    for (int r=0;r <introws;r++)
    {
        delete[] arraygame[r];
        delete[] arraygame;
        arraygame = nullptr;
    }
}
}

