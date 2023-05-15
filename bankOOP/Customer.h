#pragma once
#include <iostream>
#include "User.h"
#include "Account.h"
#include <vector>
class Customer : public User // dziedziczy publicznie z User
{
private:


public:
	Customer(int, std::string, std::string, std::string, std::string, int, int);
	virtual void show_menu() override; //funkcja wirtualna wyswietlająca interfejs dla danego typu uzytkownika
};

