#pragma once
#include <iostream>
#include "User.h"
#include "Account.h"
#include <vector>
class Customer : public User // dziedziczy publicznie z User
{
private:
	friend class Account;
	std::vector<Account*> user_accounts;
	Account* used_account;
public:
	Customer(int user_id, std::string, std::string, std::string, std::string, int, int);
	virtual void show_menu() override; //funkcja wirtualna wyswietlaj¹ca interfejs dla danego typu uzytkownika
	int show_user_id(); //?
	void set_Active();
	std::string encrypt_password(std::string);
	void create_user(User* customer);
	void show_user_data();
	void show_accounts();
	void change_account();
	void transfers();
};

