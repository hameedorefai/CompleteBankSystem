#pragma once
#include "iostream"
#include "clsScreen.h"
#include "clsString.h"
#include "Global.h"
#include <fstream>
#include "clsString.h"
#include <string>
#include <iomanip>
#include "clsScreen.h"
#include <vector>

using namespace std;

class clsTransferLogListScreen : protected clsScreen
{
private:
    struct _strTransfersRegists
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        string Amount;
        string srcBalanceAfter;
        string destBalanceAfter;
        string UserName;
    };
    static void _PrintStructLoginRegistersRecordLine(_strTransfersRegists TransferLogRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.DateTime;
        cout << "| " << setw(8) << left << TransferLogRecord.SourceAccountNumber;
        cout << "| " << setw(8) << left << TransferLogRecord.DestinationAccountNumber;
        cout << "| " << setw(8) << left << TransferLogRecord.Amount;
        cout << "| " << setw(10) << left << TransferLogRecord.srcBalanceAfter;
        cout << "| " << setw(10) << left << TransferLogRecord.destBalanceAfter;
        cout << "| " << setw(8) << left << TransferLogRecord.UserName << endl;

    }
    static void _PrintLoginRegistersData()
    {
        fstream MyFile;
        vector <string> vLoginRegistersData;
        vector <_strTransfersRegists> strTransfers;
        _strTransfersRegists Transfer;
        MyFile.open("TransferLog.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                vLoginRegistersData = clsString::Split(Line, "#//#");
                Transfer.DateTime += vLoginRegistersData[0];
                Transfer.SourceAccountNumber += vLoginRegistersData[1];
                Transfer.DestinationAccountNumber += vLoginRegistersData[2];
                Transfer.Amount += vLoginRegistersData[3];
                Transfer.srcBalanceAfter += vLoginRegistersData[4];
                Transfer.destBalanceAfter += vLoginRegistersData[5];
                Transfer.UserName += vLoginRegistersData[6];
                strTransfers.push_back(Transfer);
               // vLoginRegistersData.clear();
            }
            MyFile.close();
        }

        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t    (" + to_string(strTransfers.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


        if (vLoginRegistersData.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        for (_strTransfersRegists Transfer : strTransfers)
        {
            _PrintStructLoginRegistersRecordLine(Transfer);
        }
    }

public:

    static void ShowTransferLogListScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pLoginRegisters))
        {
            return;
        }
       // system("pause>0");
        _DrawScreenHeader("Login Registers Screen");
        _PrintLoginRegistersData();
    }
};

