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
	virtual int show_user_id() = 0;
	virtual void set_Active(User *customer) = 0;
	virtual std::string encrypt_password(std::string) = 0;
	virtual void create_user(User* customer) = 0;
};

