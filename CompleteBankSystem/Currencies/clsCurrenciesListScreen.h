#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>

class clsCurrenciesListScreen :protected clsScreen
{
private:
    static void _PrintCurrencyRecordLine(clsCurrency Currency)
    {

        cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.Country();
        cout << "| " << setw(8) << left << Currency.CurrencyCode();
        cout << "| " << setw(45) << left << Currency.CurrencyName();
        cout << "| " << setw(10) << left << Currency.Rate();

    }
public:    

    static void PrintCurrencyList()
    {
        vector <clsCurrency> vCurrenciesList = clsCurrency::GetCurrenciesList();
        string Title = "Currencies List Screen";
        string Subtitle = "\t  (" + to_string(vCurrenciesList.size()) + ") Currency.";
        _DrawScreenHeader(Title, Subtitle);
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(8) << "Code";
        cout << "| " << left << setw(45) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        if (vCurrenciesList.size() == 0)
            cout << "\t\t\t\tNo Currencies Available In the System!";
        for (clsCurrency Currency : vCurrenciesList)
        {
            _PrintCurrencyRecordLine(Currency);
            cout << endl;
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

    }

};

