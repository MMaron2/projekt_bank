﻿#include <stdio.h>
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
	database->generate_user_id(); //po co to tu jest?
	Menu(database);
	return 0;
	
}

void Menu(Database *database)
{
	int choice;
	std::cout << "Wybierz co chcesz zrobic 0 logowanie 1 rejestracja";
	std::cin >> choice;

	switch (choice)
	{
	case 0:
		Login(database);
		break;
	case 1:
		Register(database);
		break;
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
	int is_customer = database->check_customer(user_ID);
	if (is_customer == 1)
	{
		User *customer = database->get_customer_data_by_id(user_ID);
		customer->set_Active(customer);
		customer->show_menu();
		return;
		
	}
	// jeszcze trzeba w bazie danych dodać funkcje to obsługujące
	int is_employee = database->check_employe(user_ID);
	if (is_employee == 1)
	{
		/*User* customer = database->get_employee_data_by_id(user_ID);
		customer->set_Active(customer);
		customer->show_menu();
		return;*/
	}
	int is_admin = database->check_admin(user_ID);
	if(is_admin == 1)
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


	int user_id = database->generate_user_id();
	User* customer = new Customer(user_id, firstname, lastname, email, password, phonenumber, 1);
	std::string encrypted_password = customer->encrypt_password(password);

	database->create_user(user_id, firstname, lastname,  email, encrypted_password, phonenumber);
	//przeslanie danych do bazy
	//go to menu dla uzytkownikow
	customer->show_menu();

}

