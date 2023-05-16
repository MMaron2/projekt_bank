#pragma once
#include <iostream>
#include "User.h"
#include "Account.h"
#include <vector>
class Customer : public User // dziedziczy publicznie z User
{
private:


public:
	Customer(int user_id, std::string, std::string, std::string, std::string, int, int);
	virtual void show_menu() override; //funkcja wirtualna wyswietlająca interfejs dla danego typu uzytkownika
	virtual int show_user_id() override;
	virtual void set_Active(User* customer) override;
	virtual void encrypt_password(std::string) override;
};

