#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>
#include "clsInputValidate.h"


class FindCurrencyScreen : protected clsScreen
{

private:
	enum enFind{ eCode = 1, eCountry = 2};
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
	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\nCurrency Was not Found :-(\n";
		}
	}


public:

	static void ShowFindCurrency()
	{
		cout << "Find by : [1] Code or [2] Country : ";
		enFind Choice = enFind(clsInputValidate::ReadIntNumberBetween(1, 2));

	//	switch (Choice)
		
		if (enFind::eCode == Choice)
		{
			cout << "Enter CurrencyCode : ";
			string Code = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(Code);
			_ShowResults(Currency);
		}
		else if (enFind::eCountry == Choice)
		{
			cout << "Enter CurrencyCountry : ";
			string Country = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResults(Currency);
		}		
	
	}
};

