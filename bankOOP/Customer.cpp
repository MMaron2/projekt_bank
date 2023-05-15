#include "Customer.h"
#include <iostream>

Customer::Customer(int account_id_, int user_id_, std::string first_name_, std::string last_name_, std::string email_, std::string password_, int phone_number_)
	: User(user_id_, first_name_, last_name_, email_, password_, phone_number_)
{
	account_id = account_id_;
}

void Customer::show_menu()
{
	std::cout << "[1] - customer" << std::endl;
}