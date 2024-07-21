#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "FindCurrencyScreen.h"

class clsUpdateCurrencyScreen : protected clsScreen
{
private:
	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();

		cout << "\n_____________________________\n";

	}


public:

	 static void ShowUpdateRateScreen()
	{
		 _DrawScreenHeader("\tUpdate Currency Screen");
		cout << "Enter Currenct Code : ";
		string cCode = clsInputValidate::ReadString();
		clsCurrency Currency = clsCurrency::FindByCode(cCode);
		if (!Currency.IsEmpty())
		{
			_PrintCurrency(Currency);
			cout << "Are you sure you want to update rate? y/n : ";
			string Answer = clsInputValidate::ReadString();
		
			if (Answer == "y" || Answer == "Y")
			{
				cout << "\n\nUpdate Currency  Rate:";
				cout << "\n_______________________\n";
				cout << "Enter a new rate : ";
				double Number = clsInputValidate::ReadDblNumber();
				Currency.UpdateRate(Number);
				cout << "\n_______________________\n";

			}
		}
		
		}
	
	
};

