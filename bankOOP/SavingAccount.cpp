#include "SavingAccount.h"

void SavingAccount::display_account()
{
	std::cout << "\tto jest konto oszczednisowe" << std::endl;
	std::cout << "\tnumer konta: " << account_id << std::endl;
	std::cout << "\tbalance: "; std::cout << balance << std::endl;
	std::cout << "\taccount type: " << account_type << std::endl;
}
void SavingAccount::display_account_type()
{
	std::cout << "Konto oszczednosciowe";
}

void SavingAccount::show_balance()
{
	std::cout << "Stan konta: ";
	std::cout << balance << std::endl;
	system("pause");
}
