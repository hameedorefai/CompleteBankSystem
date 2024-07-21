#pragma once
#include "iostream"
#include "clsScreen.h"
#include "clsString.h"
#include "Global.h"
#include <fstream>
#include "clsUtil.h"
class clsLoginRegistersScreen : protected clsScreen
{
private:
    struct _strLoginRegisters
    {
        string DateTime;
        string UserName;
        string Password;
        string Permissions;
    };
    static void _PrintStructLoginRegistersRecordLine(_strLoginRegisters User)
    {

        cout << setw(8) << left << "" << "| " << setw(35) << left << User.DateTime;
        cout << "| " << setw(20) << left << User.UserName;
        cout << "| " << setw(20) << left << clsUtil::DecryptText(User.Password);
        cout << "| " << setw(10) << left << User.Permissions << endl;

    }
	static void _PrintLoginRegistersData()
	{
         fstream MyFile;
         vector <string> vLoginRegistersData;
         vector <_strLoginRegisters> strUsers;
         MyFile.open("LoginsRegisterList.txt", ios::in);
         if (MyFile.is_open())
         {
             string Line;
             _strLoginRegisters User;
             while (getline(MyFile, Line))
             {
                 vLoginRegistersData = clsString::Split(Line, "#//#");
                 User.DateTime = vLoginRegistersData[0];
                 User.UserName = vLoginRegistersData[1];
                 User.Password= vLoginRegistersData[2];
                 User.Permissions = vLoginRegistersData[3];
                 strUsers.push_back(User);
             }
             MyFile.close();
         }
        
         cout << setw(8) << left << "" << "\n\t_______________________________________________________";
         cout << "_________________________________________\n" << endl;

         cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
         cout << "| " << left << setw(20) << "UserName";
         cout << "| " << left << setw(20) << "Password";
         cout << "| " << left << setw(10) << "Permissions";
         cout << setw(8) << left << "" << "\n\t_______________________________________________________";
         cout << "_________________________________________\n" << endl;

         if (vLoginRegistersData.size() == 0)
             cout << "\t\t\t\tNo Logins Available In the System!";
         for (_strLoginRegisters User : strUsers)
         {
             _PrintStructLoginRegistersRecordLine(User);
         }
	}

public:
	static void ShowLoginRegistersScreen()
	{
        if (!CheckAccessRights(clsUser::enPermissions::pLoginRegisters))
        {
            return;
        }

		_DrawScreenHeader("Login Registers Screen");
		_PrintLoginRegistersData();
	}
};

