#include "NormalAccount.h"
#include <iostream>
#include <string.h>

//NormalAccount::NormalAccount(double balance_) : Account(balance_)
//{
//}


void NormalAccount::display_account()
{

	std::cout << "to jest konto konsumenckie" << std::endl;
	std::cout << "balance: "; std::cout << balance << std::endl;
	std::cout << "account type: " << account_type;
}

void NormalAccount::display_account_type()
{
	std::cout << "Konto konsumenckie";
}
