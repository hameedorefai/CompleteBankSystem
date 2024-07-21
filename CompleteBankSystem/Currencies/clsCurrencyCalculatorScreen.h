#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "FindCurrencyScreen.h"

class clsCurrencyCalculatorScreen 
{
private:
	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();
		cout << "\n_____________________________\n";

	}

	static void _Exchange(string Currency1Code, string Currency2Code, double Amount)
	{
		clsCurrency Currency1 = clsCurrency::FindByCode(Currency1Code);
		clsCurrency Currency2 = clsCurrency::FindByCode(Currency2Code);

		cout << "\nConvert from:\n";
		_PrintCurrency(Currency1);
		cout << "\nConvert To:\n";
		_PrintCurrency(Currency2);

		double ToUSD =  100 / Currency1.Rate() ;
		double Exchange = ToUSD * Currency2.Rate();
		cout << Amount << " " << Currency1.CurrencyCode() << " = " << Exchange << " " << Currency2.CurrencyCode() << endl;
		// Maybe we have a problem here, but it's ok.
	}

public:

	static void ShowCurrencyCalculator()
	{
		string Continue = "";

		do
		{
			string Currency1Code;
			do
			{
				cout << "Enter Currency1 Code : ";
				Currency1Code = clsInputValidate::ReadString();
			} while (!clsCurrency::IsCurrencyExist(Currency1Code));

			string Currency2Code;
			do
			{
				cout << "Enter Currency2 Code : ";
				Currency2Code = clsInputValidate::ReadString();
			} while (!clsCurrency::IsCurrencyExist(Currency2Code));

			cout << "Enter Amount to Exchange : ";
			double Amount = clsInputValidate::ReadDblNumber();
			_Exchange(Currency1Code, Currency2Code, Amount);
			

			cout << "Do you want to perform another calculate? y/n : ";
			Continue = clsInputValidate::ReadString();
		} while (Continue == "y" || Continue == "Y");
	}

};

