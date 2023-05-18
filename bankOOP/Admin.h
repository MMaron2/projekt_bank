#pragma once
#include "Employee.h"
#include <iostream> 
class Admin :public Employee
{
public:
	Admin(bool, bool, int, std::string, std::string, std::string, std::string, int, int);
	virtual void show_menu() override;
	void users_list();
	void employe_list();
	void delete_customer_account();
	void create_employe_account();
};

