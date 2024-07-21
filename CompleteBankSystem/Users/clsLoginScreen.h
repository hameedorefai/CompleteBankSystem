#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"
//#include "clsRegisterLogins.h"

class clsLoginScreen :protected clsScreen
{

private:


    static  void _Login()
    {
        bool LoginFaild = false;

        string Username, Password;
        for (int Counter = 2; Counter >= 0; Counter--)
        {
            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();


            if (LoginFaild)
            {
                cout << "\nInvlaid Username/Password!\n";
                cout << "You have " << Counter << " Triel(s) to login.\n\n";
                if (Counter == 0)
                {
                    cout << "\n\nYou are locked after 3 failed tries\n\n";
                    CurrentUser.Block();
                }
            }
            else
            {
                CurrentUser.RegistTheLogin();
                clsMainScreen::ShowMainMenue();
                break;

            }
        }
    }

public:


    static void ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        _Login();

    }

};

