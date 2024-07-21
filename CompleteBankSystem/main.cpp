#include <iostream>
#include "clsLoginScreen.h"
#include "clsUtil.h"
using namespace std;


int main()
{
	while (!CurrentUser.Blocked())
	{
		clsLoginScreen::ShowLoginScreen();
		
	}
	return 0;
}