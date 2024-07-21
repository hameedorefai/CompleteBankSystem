#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "FindCurrencyScreen.h"
#include "clsUpdateCurrencyScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyMainScreen : protected clsScreen
{

    enum enCurrencyExchangeMenueOptions
    {
        ListCurrencies = 1, FindCurrency = 2, UpdateRate = 3, CurrencyCalculator = 4, MainMenue = 5
    };

    static short _ReadCurrencyExchangeMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadIntNumberBetween(1, 10, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static void _ShowListCurrencies()
    {
       // cout << "Show List Currencies will be here soon..\n";
        clsCurrenciesListScreen::PrintCurrencyList();
    }
                
    static void _ShowFindCurrency()
    {
       //cout << "Show Find Currency will be here soon..\n";
        FindCurrencyScreen::ShowFindCurrency();

    }
                
    static void _ShowUpdateRateScreen()
    {
      // cout << "Show Update RateScreen will be here soon..\n";
        clsUpdateCurrencyScreen::ShowUpdateRateScreen();
    }
                
    static void _ShowCurrencyCalculator()
    {
       cout << "Show Currency Calculator will be here soon..\n";
       clsCurrencyCalculatorScreen::ShowCurrencyCalculator();
    }

    static void _GoBackToCurrencyExchangeMenueScreen()
    {
        cout << "\n\nPress any key to go back to Currency Exchange Menue Screen.\n\n";
        system("pause>0");
        ShowCurrencyExchangeMenue();
    }

    static void _PerfromCurrencyExchangeMenueOption(enCurrencyExchangeMenueOptions CurrencyExchangeOption)
    {
        
            switch (CurrencyExchangeOption)
            {
            case enCurrencyExchangeMenueOptions::ListCurrencies:
            {
                system("cls");
                _ShowListCurrencies();
                _GoBackToCurrencyExchangeMenueScreen();
                break;
            }
            case enCurrencyExchangeMenueOptions::FindCurrency:
                system("cls");
                _ShowFindCurrency();
                _GoBackToCurrencyExchangeMenueScreen();
                break;

            case enCurrencyExchangeMenueOptions::UpdateRate:
                system("cls");
                _ShowUpdateRateScreen();
                _GoBackToCurrencyExchangeMenueScreen();
                break;

            case enCurrencyExchangeMenueOptions::CurrencyCalculator:
                system("cls");
                _ShowCurrencyCalculator();
                _GoBackToCurrencyExchangeMenueScreen();
                break;

            case enCurrencyExchangeMenueOptions::MainMenue:
                
                break;
            }

        }

    
public:


    static void ShowCurrencyExchangeMenue()
    {

        system("cls");
        _DrawScreenHeader("\t\tCurrency Exchange Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tCurrency Exchange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromCurrencyExchangeMenueOption((enCurrencyExchangeMenueOptions)_ReadCurrencyExchangeMenueOption());
    }


};

