#include <iostream>
#include "libZspace.h"

using namespace std;
using namespace ZorkSpace;
int main(int argc,char** argv)
{
    srand(time(nullptr));
    Game gruegame;
    twoDArray ArrayG;
    ValidateArgument(argv ,argc);
    gruegame.intRows = Convtoint(argv[1]);
    gruegame.intCols = Convtoint(argv[2]);
    gruegame.Numbatteries = Convtoint(argv[3]);
    ArrayG= AllocateAndInit(gruegame.intRows,gruegame.intCols,gruegame.Numbatteries);
    int TurnsB4dawn = (gruegame.Numbatteries*2);


do
{
    system("cls");
    if (gruegame.blnlights == true)
    {
        PrintArray(gruegame.intRows, gruegame.intCols,ArrayG);
    }else if(gruegame.blnlights ==false)
    {
         cout << "            TORCH IS OFF\n";
        TorchOff(ArrayG,gruegame.intRows,gruegame.intCols);
    }
    OutputMenu(TurnsB4dawn);
    cout << "Choose An option: ";
    cin >>gruegame.Opt;
    gruegame.Opt = toupper(gruegame.Opt);
    switch(gruegame.Opt)
    {
         case 'W':
         case 'S':
         case 'A':
         case 'D':
             {
                 Moveplayer(ArrayG,gruegame.intRows,gruegame.intCols,gruegame.Opt,TurnsB4dawn,gruegame.blnContinue,gruegame.Numbatteries);
                 break;
             }
             case 'Q':
             {
            system("cls");
            cout <<"*************************************\n"<< "*******GAME ENDED! YOU'VE QUIT*******"<<endl
            <<"*************************************\n";
            gruegame.blnContinue = false;
            exit(0);
             }
             case 'O':
             {
                   gruegame.blnlights =false;
                   MoveplayerinD(ArrayG,gruegame.Opt,TurnsB4dawn,gruegame.blnContinue);
                    break;
                }
             case 'T':
                {
                   gruegame.blnlights = true;
                    break;
                }
    default:
        {
            cerr << "Invalid Option! Choose from the ones listed" <<endl;
            cout << "Choose movement: ";
            cin >>gruegame.Opt;
            gruegame.Opt = toupper(gruegame.Opt);
            system("pause");
            break;
        }
    }


}while(gruegame.blnContinue == true);
Deallocate(ArrayG,gruegame.intRows);
    return 0;
}
