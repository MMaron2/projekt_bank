#pragma once
#include <iostream>
#include "User.h"
#include "Account.h"
#include <vector>
class Customer : public User // dziedziczy publicznie z User
{
private:
	int account_id; //numer konta ale to bym przeniós³ do Account zeby konto mia³o swoj numer !!!!!!!

public:
	Customer(int, int, std::string, std::string, std::string, std::string, int);
	virtual void show_menu() override; //funkcja wirtualna wyswietlaj¹ca interfejs dla danego typu uzytkownika
	std::vector<Account*> user_acounts; // tablica przechowuj¹ca konta u¿ytkownika. Jak sie to do bazy danych pod³¹czy to bêdzie poprostu pobierac z bazy
	void add_account_to_vector(Account* account)// funkcja dodaje konta to vectora
	{
		user_acounts.push_back(account);
	}

};

