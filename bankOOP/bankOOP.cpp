#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "User.h"
#include "Employee.h"
#include "Customer.h"
#include "Admin.h"
#include "Database.h"
#include "Account.h"
#include "NormalAccount.h"
#include "SavingAccount.h"

void Menu();
void Menu_for_customers(User* customer);
void show_profile_page(User* customer);
// pozniej mozna przemyslec czy nie schowac tych metod register i login do klasy user/customer zeby mniejszy syf byl
void Login();
void Register();

Database database;
int main()
{
	Menu();
	return 0;
	
}

void Menu()
{
	int choice;
	std::cout << "Wybierz co chcesz zrobic 0 logowanie 1 rejestracja";
	std::cin >> choice;

	switch (choice)
	{
	case 0:
		Login();
		break;
	case 1:
		Register();
		break;
	}

}

void Login()
{
	// logujemy sie przez userID
	int user_ID;
	std::string password;

	std::cout << "Podaj login";
	std::cin >> user_ID;

	std::cout << "Podaj haslo";
	std::cin >> password;

	//sprawdzanie typu uzytkowania
	int is_customer = database.check_customer(user_ID);
	if (is_customer == 0)
	{
		User  *customer = database.get_customer_data_by_id(user_ID);
		customer->set_Active(customer);
		Menu_for_customers(customer);
		
	}
	else
	{

		int is_employee = database.check_employe(user_ID);
		if (is_employee == 0)
		{
			//logowanie do pracowniczemu menu
			std::cout << "zalogowano admin";
		}
		else
		{
			//zle dane logowania
			std::cout << "niepoprawne dane";
		}
	}


}

void Register()
{
	int phonenumber;
	std::string firstname, lastname, password, email, addres;

	std::cout << "Podaj Imie";
	std::cin >> firstname;

	std::cout << "Podaj Naziwsko";
	std::cin >> lastname;

	std::cout << "Podaj Adres";
	std::cin >> addres;

	std::cout << "Podaj numer telefonu";
	std::cin >> phonenumber;

	std::cout << "Podaj haslo";
	std::cin >> password;
	std::cout << password;

	//Todo: generate user_id
	int user_id = 1333;
	User* customer = new Customer(user_id, firstname, lastname, email, password, phonenumber, 1);
	customer->encrypt_password(password);

	//go to menu dla uzytkownikow
	Menu_for_customers(customer);

}

void Menu_for_customers(User* customer)
{
	system("cls");

	//tutaj Menu wlasciwe, przelewy itd
	int choice;
	std::cout << "Wybierz co chcesz zrobic 0 wyslanie przelewu 1 historia konta 2 dane profilu 3 dzial oszczedzanie";
	std::cin >> choice;

	switch (choice)
	{
	case 0:
		
		break;
	case 1:
		
		break;
	case 2:
		show_profile_page(customer);
		break;
	}

}

