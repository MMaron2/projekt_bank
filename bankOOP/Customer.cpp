#include "Customer.h"
#include <iostream>

Customer::Customer(int user_id_, std::string first_name_, std::string last_name_, std::string email_, std::string password_, int phone_number_, int is_active_)
	: User(user_id_, first_name_, last_name_, email_, password_, phone_number_, is_active_)
{
}

void Customer::show_menu()
{ 
	std::cout << "[1] - customer" << std::endl;
	std::cout << user_id << std::endl;
	std::cout << first_name << std::endl;
	std::cout << last_name << std::endl;
	std::cout << email << std::endl;
	std::cout << password << std::endl;
	std::cout << phone_number << std::endl;
	std::cout << is_active << std::endl;

}
