#include "Employee.h"
#include <iostream>

Employee::Employee(bool is_admin_, bool is_staff_, int user_id_, std::string first_name_, std::string last_name_, std::string email_, std::string password_, int phone_number_)
	:User(user_id_, first_name_, last_name_, email_, password_, phone_number_)
{
	is_admin = is_admin_;
	is_staff = is_staff_;
}

void Employee::show_menu()
{
	std::cout << "[1] - employee\n";
}
