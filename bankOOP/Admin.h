#pragma once
#include "Employee.h"
#include <iostream> 
class Admin :public Employee
{
public:
	Admin(bool, bool, int, std::string, std::string, std::string, std::string, int);
	virtual void show_menu() override;
};

