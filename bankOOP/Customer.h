#pragma once
#include <iostream>
#include "User.h"
#include "Account.h"
#include "Transfer.h"
#include <vector>
class Customer : public User // dziedziczy publicznie z User
{
private:
	friend class Account;
	friend class Transfer;
	std::vector<Account*> user_accounts;
	std::vector<Transfer*> transfers;
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
	// dodanie sprawdzenia czy istnieje konto o takim numerze
	void transfer();
	void add_new_account();
	void show_transfer_history();
};

