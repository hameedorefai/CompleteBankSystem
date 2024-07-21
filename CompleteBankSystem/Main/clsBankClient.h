#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsMainScreen.h"
using namespace std;
clsInputValidate input;
clsUtil Util;
class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode };

	enMode _Mode;
	string _PinCode;
	string _AccountNumber;
	float _AccountBalance;
	bool _MarkForDelete = false;
	bool _IsEmpty()
	{
		return (_Mode == EmptyMode);
	}
	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);

	}
	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
	{
		vector <string> vClientData;
		vClientData = clsString::Split(Line, Seperator);
		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], clsUtil::DecryptText(vClientData[5]), stof(vClientData[6]));

	}
	string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string DataLine;
		DataLine += Client.FirstName + Seperator;
		DataLine += Client.LastName + Seperator;
		DataLine += Client.Email + Seperator;
		DataLine += Client.Phone + Seperator;
		DataLine += Client.AccountNumber + Seperator;
		DataLine += clsUtil::EncryptText(Client.PinCode) + Seperator;
		DataLine += to_string(Client.AccountBalance);
		return DataLine;
	}

	static vector <clsBankClient>  _LoadClientsDataFromFileToV()
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		vector <clsBankClient> vClients;

		if (MyFile.is_open())
		{
			string Line;
			// Client;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return vClients;
	}
	void _SaveClientsDataToFile(vector <clsBankClient> _vClients)
	{
		fstream ClientsFile;
		ClientsFile.open("Clients.txt", ios::out); // Editting on File, Clear file then overwrite.

		if (ClientsFile.is_open())
		{
			string DataLine;
			for (clsBankClient Client : _vClients)
			{
				if (Client.MarkedForDelete() == false)
				{
					DataLine = _ConvertClientObjectToLine(Client);
					ClientsFile << DataLine << endl;
				}
			}
			ClientsFile.close();
		}

	}
	void _AddClientDataToFile(string DataLine)
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFileToV();
		vClients.push_back(_ConvertLineToClientObject(DataLine));// I Follow mentor (in parameters).
		_SaveClientsDataToFile(vClients);
	}
	void _Update()
	{
		vector <clsBankClient> _vClients = _LoadClientsDataFromFileToV();
		for (clsBankClient& Client : _vClients)
		{
			if (Client.AccountNumber == AccountNumber)
			{
				Client = *this;
			}
		}
		_SaveClientsDataToFile(_vClients);
	}
	void _Add()
	{
		_AddClientDataToFile(_ConvertClientObjectToLine(*this));
	}
	bool _Delete()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFileToV();

		for (clsBankClient& Client : vClients)
		{
			if (_AccountNumber == Client.GetAccountNumber())
			{
				Client._MarkForDelete = true;
				break;
			}
		}
		_SaveClientsDataToFile(vClients);
		*this = _GetEmptyClientObject();
		return 1;
	}
	string _PrepareTransferLoginsRegister(double Amount, clsBankClient ClientTransferTo)
	{
		string Seperator = "#//#";
		string DataLine = "";
		DataLine += clsDate::GetSystemDateTimeString() + Seperator;
		DataLine += AccountNumber + Seperator;
		DataLine += ClientTransferTo.AccountNumber + Seperator;
		DataLine += to_string(Amount) + Seperator;
		DataLine += to_string(AccountBalance)+Seperator;
		DataLine += to_string(ClientTransferTo.AccountBalance) + Seperator;
		DataLine += CurrentUser.UserName;
		return DataLine;
	}
	void _RegistTransferLog(double Amount, clsBankClient ClientTransferTo)
	{
			fstream MyFile;
			MyFile.open("TransferLog.txt", ios::app);

			if (MyFile.is_open())
			{
				MyFile << _PrepareTransferLoginsRegister(Amount, ClientTransferTo) << endl; 
					MyFile.close();
			}
		
	}


public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone
		, string AccountNumber, string PinCode, float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_PinCode = PinCode;
		_AccountNumber = AccountNumber;
		_AccountBalance = AccountBalance;
	}
	enum enSaveResults { svFailedEmptyObject, svSucceeded, svFailedAccNumberExists };
	bool Delete()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFileToV();

		for (clsBankClient& Client : vClients)
		{
			if (_AccountNumber == Client.GetAccountNumber())
			{
				Client._MarkForDelete = true;
				break;
			}
		}
		_SaveClientsDataToFile(vClients);
		*this = _GetEmptyClientObject();
		return 1;
	}
	bool IsEmpty()
	{
		return (_Mode == EmptyMode);
	}


	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountNumber(string AccountNumber)
	{
		_AccountNumber = AccountNumber;
	}
	string GetAccountNumber()
	{
		return _AccountNumber;
	}
	__declspec(property(get = GetAccountNumber, put = SetAccountNumber)) string AccountNumber;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	string GetFullName()
	{
		return FirstName + " " + LastName;
	}
	//No UI code inside object
	//void Print()
		/*{
		cout << "\nClient Card:";
		cout << "\n________________";
		cout << "\nFirst Name : " << clsPerson::FirstName;
		cout << "\nLast Name  : " << clsPerson::LastName;
		cout << "\nFull Name  : " << clsPerson::FirstName << " " << clsPerson::LastName;
		cout << "\nEmail      : " << clsPerson::Email;
		cout << "\nPhone      : " << clsPerson::Phone;
		cout << "\nAcc. Number: " << AccountNumber;
		cout << "\nPassword   : " << PinCode;
		cout << "\nBalance    : " << AccountBalance;
		cout << "\n________________" << endl;
	}*/



	static clsBankClient Find(string AccountNumber)
	{
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); //Read only.

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}
	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		clsBankClient Client = Find(AccountNumber);
		if (Client.PinCode == PinCode)
			return Client;
		return _GetEmptyClientObject();
	}
	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);
		return (!Client._IsEmpty());
	}
	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}
	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFileToV();
	}

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::UpdateMode:
		{
			_Update();
			return svSucceeded;
		}
		case enMode::EmptyMode:
		{
			return svFailedEmptyObject;
		}
		case AddNewMode:
		{
			if (IsClientExist(AccountNumber))
			{
				return svFailedAccNumberExists;
			}
			else
			{
				_Add();
				_Mode = UpdateMode;
				return enSaveResults::svSucceeded;
			}
		}

		}
	}
	bool MarkedForDelete()
	{
		return _MarkForDelete;
	}

	void ReadClientInfo(clsBankClient Client)
	{
		cout << "Enter First Name   : ";
		Client.FirstName = input.ReadString();

		cout << "Enter Last Name    : ";
		Client.LastName = input.ReadString();

		cout << "Enter Email        : ";
		Client.Email = input.ReadString();

		cout << "Enter Phone        : ";
		Client.Phone = input.ReadString();

		cout << "Enter PinCode      : ";
		Client.PinCode = input.ReadString();

		cout << "Enter Acc. Balance : ";
		Client.AccountBalance = input.ReadDblNumber();
	}

	void UpdateClient()
	{
		string AccountNumber;

		cout << "\nEnter Client Account number : ";
		AccountNumber = input.ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not found, choose another one : ";
			AccountNumber = input.ReadString();
		}
		clsBankClient Client = Find(AccountNumber);

		//Client.Print();

		ReadClientInfo(Client);

		enSaveResults SaveResults = Client.Save();


	}

	void AddNewClient()
	{

		string AccountNumber;
		cout << "Enter AccountNumber? ";
		AccountNumber = input.ReadString();

		while (IsClientExist(AccountNumber))
		{
			cout << "Client with [" << AccountNumber << "] is already exists,";
			cout << " Enter another Account Number? ";
			AccountNumber = input.ReadString();
		}

		clsBankClient Client = GetAddNewClientObject(AccountNumber);
		ReadClientInfo(Client);
	}

	void DeleteClient()
	{
		string AccountNumber;
		cout << "Enter AccountNumber? ";
		AccountNumber = input.ReadString();

		while (!IsClientExist(AccountNumber))
		{
			cout << "Client with [" << AccountNumber << "] is Not exists,";
			cout << " Enter another Account Number? ";
			AccountNumber = input.ReadString();
		}
		clsBankClient Client = Find(AccountNumber);
		//Client.Print();
		cout << "Are you sure you want to delete this client? ";
		string Answer = "n";
		cin >> Answer;
		if (Answer == "y" || Answer == "Y")
		{
			if (Client._Delete())
			{
				cout << "Client Was Deleted\n";
				//	Client.Print();
			}
			else
			{
				cout << "Client Was not deleted\n";
			}
		}
	}

	static void ShowClientsList()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFileToV();
		cout << "\n\t\t\t\t\tClients List (" << vClients.size() << ") Clients(s)." << endl;
		cout << "\n_________________________________________________________";
		cout << "__________________________________________\n" << endl;
		cout << "| " << left << std::setw(15) << "Account Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n_________________________________________________________";
		cout << "__________________________________________\n" << endl;

		for (clsBankClient Client : vClients)
		{
			cout << "| " << setw(15) << Client.AccountNumber;
			cout << "| " << setw(40) << Client.GetFullName();
			cout << "| " << setw(12) << Client.Phone;
			cout << "| " << setw(10) << Client.PinCode;
			cout << "| " << setw(12) << Client.AccountBalance;
			cout << endl;
		}
	}
	static void ShowTotalBalances()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFileToV();
		cout << "\n\t\t\t\t\tBalance List (" << vClients.size() << ") Clients(s)." << endl;
		cout << "\n_________________________________________________________";
		cout << "__________________________________________\n" << endl;
		cout << "| " << left << std::setw(15) << "Account Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n_________________________________________________________";
		cout << "__________________________________________\n" << endl;

		double AllBalances = 0;
		for (clsBankClient Client : vClients)
		{
			cout << "| " << setw(15) << Client.AccountNumber;
			cout << "| " << setw(40) << Client.GetFullName();
			cout << "| " << setw(12) << Client.AccountBalance;
			AllBalances += Client.AccountBalance;

			cout << endl;
		}

		cout << "\n\t\t\t Total Balances : " << AllBalances;
		cout << "\n\t\t\t(" << Util.NumberToText((int)AllBalances) << ")" << endl;
	}
	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}
	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}
	static double GetTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient Client : vClients)
		{

			TotalBalances += Client.AccountBalance;
		}

		return TotalBalances;
	}

	bool Transfer(double Amount, clsBankClient&ClientTransferTo)
	{
		while (!Withdraw(Amount))
		{
			cout << "Amount Exceeds the Available blanance, Enter another amount : ";
			Amount = clsInputValidate::ReadDblNumber();
		}
		cout << "\nAre you sure you want to perform this transaction? ";

		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			ClientTransferTo.Deposit(Amount);
		}
		_RegistTransferLog(Amount, ClientTransferTo);
		return true;
	}

};









