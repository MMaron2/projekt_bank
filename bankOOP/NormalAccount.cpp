#include "NormalAccount.h"
#include <iostream>
#include <string.h>

void NormalAccount::display_account()
{
	std::cout << "\tto jest konto konsumenckie" << std::endl;
	std::cout << "\tnumer konta: " << account_id << std::endl;
	std::cout << "\tbalance: "; std::cout << balance << std::endl;
	std::cout << "\taccount type: " << account_type << std::endl;
}

void NormalAccount::display_account_type()
{
	std::cout << "Konto konsumenckie";
}

void NormalAccount::show_balance()
{
	std::cout << "Stan konta: ";
	std::cout << balance << std::endl;
	system("pause");
}
