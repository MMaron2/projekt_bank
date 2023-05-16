#include "Customer.h"
#include <iostream>

Customer::Customer(int user_id_, std::string first_name_, std::string last_name_, std::string email_, std::string password_, int phone_number_, int is_active_)
	: User(user_id_, first_name_, last_name_, email_, password_, phone_number_, is_active_)
{
}

void Customer::show_menu()
{

	//tutaj Menu wlasciwe, przelewy itd
	int choice = 0;

	while (choice != 2)
	{
		std::cout << "[1] - przelewy\n";
		std::cout << "[2] - stan konta\n";
		std::cout << "[3] - wyloguj\n";
		try
		{
			std::cin >> choice;
		}
		catch (...)
		{
			std::cout << "wprowadzono zle dane\n";
			continue;
		}
		switch (choice)
		{
			case 1:
				break;
			case 2:
				break;
			default:
				break;
		}
	}
}

int Customer::show_user_id()
{
	return user_id;
}

void Customer::set_Active(User* customer)
{
	is_active = 1;
}

void Customer::encrypt_password(std::string pass)
{
    std::string result = "";

    for (char c : pass) {
        if (isalpha(c)) {
            char shifted_c = toupper(c) + 1;
            if (shifted_c > 'Z') {
                shifted_c -= 26;
            }
            result += shifted_c;
        }
        else {
            result += c;
        }
    }
    password = result;
}
