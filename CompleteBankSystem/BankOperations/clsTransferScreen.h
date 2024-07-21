#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;


class clsTransferScreen : protected clsScreen
{
private:
    enum _enTransfer{From,To};
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << Client.GetFullName();
        cout << "\nAcc. Number : " << Client.AccountNumber;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }
    static string _ReadAccountNumber(string Message)
    {
        string AccountNumber = "";
        cout << "Please enter Account Number to " << Message;
        cin >> AccountNumber;
        return AccountNumber;
    }
    static clsBankClient _ReadClient(_enTransfer TranserTybe)
    {
        string Message = "";
        if (TranserTybe == _enTransfer::From)
            Message = "Transfer from : ";
        else
            Message = "Transfer To : ";


        string AccountNumber = _ReadAccountNumber(Message);
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber(Message);
        }
        return clsBankClient::Find(AccountNumber);
    }

public:

    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\t   Transfer Screen");


        clsBankClient ClientTransferFrom = _ReadClient(From);
        _PrintClient(ClientTransferFrom);

        clsBankClient ClientTransferTo = _ReadClient(To);
        _PrintClient(ClientTransferTo);


        double Amount = 0;
        cout << "\nPlease enter Transfer Amount? ";
        Amount = clsInputValidate::ReadDblNumber();

        if (ClientTransferFrom.Transfer(Amount, ClientTransferTo))
        {
            cout << "\nTransfer done Successfully.\n";
            _PrintClient(ClientTransferFrom);
            _PrintClient(ClientTransferTo);
        }
        else
        {
            cout << "Transfer Failed Successfully.\n";
        }

        }
    
    
};