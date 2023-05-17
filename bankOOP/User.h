#pragma once
#include <iostream>
#include "User.h"

class User
{
protected:
	int user_id;
	std::string first_name;
	std::string last_name;
	std::string email;
    std::string password;
	int phone_number;
	int is_active;

public:
	User(int, std::string, std::string, std::string, std::string, int, int);
	virtual void show_menu() = 0;
};

