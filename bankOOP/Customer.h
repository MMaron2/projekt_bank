#pragma once
#include <iostream>
#include "User.h"
#include "Account.h"
#include <vector>
class Customer : public User // dziedziczy publicznie z User
{

public:
	Customer(int, std::string, std::string, std::string, std::string, int, int);
	virtual void show_menu() override; //funkcja wirtualna wyswietlaj�ca interfejs dla danego typu uzytkownika
	//std::vector<Account*> user_acounts; // tablica przechowuj�ca konta u�ytkownika. Jak sie to do bazy danych pod��czy to b�dzie poprostu pobierac z bazy
	//void add_account_to_vector(Account* account)// funkcja dodaje konta to vectora
	//{
	//	user_acounts.push_back(account);
	//}



};

