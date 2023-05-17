#include "Admin.h"
#include <iostream>

Admin::Admin(bool is_admin_, bool is_staff_, int user_id_, std::string first_name_, std::string last_name_, std::string email_, std::string password_, int phone_number_, int is_active_)
	:Employee(is_admin_, is_staff_, user_id_, first_name_, last_name_, email_, password_, phone_number_, is_active_){
}

void Admin::show_menu()
{
	std::cout << "[1] - Lista pracownikow\n";
	std::cout << "[2] - Usuwanie konta\n";
}