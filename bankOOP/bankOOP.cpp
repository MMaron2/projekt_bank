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

void Menu(Database *database);
// pozniej mozna przemyslec czy nie schowac tych metod register i login do klasy user/customer zeby mniejszy syf byl
void Login(Database *database);
void Register(Database *database);


int main()
{

	Database *database = new Database();
	//database->generate_user_id(); //po co to tu jest?
	Menu(database);
	delete database;
	return 0;
	
}

void Menu(Database *database)
{
	int choice = 0;
	while (choice != 3)
	{
		std::cout << "[1] - logowanie\n";
		std::cout << "[2] - rejestracja\n";
		std::cout << "[3] - zakoncz\n";
		try
		{
			std::cin >> choice;
		}
		catch (...)
		{
			system("cls");
			std::cout << "prosze wpisac pin" << std::endl;
			continue;
		}
		

		switch (choice)
		{
		case 1:
			Login(database);
			break;
		case 2:
			Register(database);
			break;
		case 3:
			return;
		default:
			break;
		}
	}

}

void Login(Database *database)
{
	// logujemy sie przez userID
	int user_ID;
	std::string password;

	std::cout << "Podaj login";
	std::cin >> user_ID;

	std::cout << "Podaj haslo";
	std::cin >> password;

	//sprawdzanie typu uzytkowania
	if (database->check_customer(user_ID))
	{
		User *customer = database->get_customer_data_by_id(user_ID);
		customer->set_Active(customer);
		customer->show_menu();
	}
	//jeszcze trzeba w bazie danych dodać funkcje to obsługujące
	else if(database->check_employe(user_ID))
	{
		/*User* customer = database->get_employee_data_by_id(user_ID);
		customer->set_Active(customer);
		customer->show_menu();
		return;*/
	}
	if(database->check_admin(user_ID))
	{
		/*User* customer = database->get_admin_data_by_id(user_ID);
		customer->set_Active(customer);
		customer->show_menu();
		return;*/
	}

	std::cout << "podano zly login lub haslo" << std::endl;
	
}

void Register(Database *database)
{
	int phonenumber;
	std::string firstname, lastname, password, email, addres;

	std::cout << "Podaj Imie";
	std::cin >> firstname;

	std::cout << "Podaj Naziwsko";
	std::cin >> lastname;

	std::cout << "Podaj Adres";
	std::cin >> addres;

	std::cout << "Podaj email";
	std::cin >> email;

	std::cout << "Podaj numer telefonu";
	std::cin >> phonenumber;

	std::cout << "Podaj haslo";
	std::cin >> password;


	// to trzeba zmienić zeby wracało do login i wymagało logowania po zarejestrowaniu
	int user_id = database->generate_user_id();
	User* customer = new Customer(user_id, firstname, lastname, email, password, phonenumber, 1);
	std::string encrypted_password = customer->encrypt_password(password);

	database->create_user(user_id, firstname, lastname,  email, encrypted_password, phonenumber);
	//przeslanie danych do bazy
	//go to menu dla uzytkownikow
	customer->show_menu();

}

