#include <iostream>
#include "User.h"
#include "Employee.h"
#include "Customer.h"
#include "Admin.h"
#include "Database.h";
#include "Account.h";
#include "NormalAccount.h"
#include "SavingAccount.h"

int main()
{
	// testy bazy danych
	Database database;
	database.connect_database();
	/*database.select_all_Accounts_from_database();*/
	database.select_user_data(5);
	std::cout << "----------------------------" << std::endl;
	// testy dla Account
	Account* account = new NormalAccount(123.3,0);
	account->display_account();
	std::cout << "\n----------------------------" << std::endl;
	account = new SavingAccount(144.5, 1);
	account->display_account();
	std::cout << "\n----------------------------" << std::endl;

	// testy dla User
	User* user = new Customer(1, 1, "hyla", "hyla", "hyla", "hyla", 1);
	user->show_menu();
	std::cout << "---------------------------------------" << std::endl;
	user = new Employee(1, 1, 1, "hyla", "hyla", "hyla", "hyla", 1);
	user->show_menu();
	std::cout << "---------------------------------------" << std::endl;
	user = new Admin(1, 1, 1, "hyla", "hyla", "hyla", "hyla", 1);
	user->show_menu();

	return 0;
	
}

