#include "SavingAccount.h"

void SavingAccount::display_account()
{
	std::cout << "to jest konto oszcz�dno�ciowe" << std::endl;
	std::cout << "balance: "; std::cout << balance << std::endl;
	std::cout << "account type: " << account_type;
}

void SavingAccount::display_account_type()
{
	std::cout << "Konto oszczednosciowe";
}
