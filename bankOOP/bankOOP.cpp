#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <regex>
#include <openssl/ssl.h>
#include "User.h"
#include "Employee.h"
#include "Customer.h"
#include "Admin.h"
#include "Database.h"
#include "Account.h"
#include "NormalAccount.h"
#include "SavingAccount.h"

void Menu(Database *database, User *customer);
// pozniej mozna przemyslec czy nie schowac tych metod register i login do klasy user/customer zeby mniejszy syf byl
void Login(Database *database, User *customer);
void Register(Database *database);

int main()
{
	User* customer  = nullptr;
	Database *database = new Database();
	Menu(database, customer);
	delete database;
	delete customer;
	return 0;
}

void Menu(Database *database, User *customer)
{
	int choice = 0;
	while (choice != 3)
	{
		system("cls");
		std::cout << "[1] - logowanie\n";
		std::cout << "[2] - rejestracja\n";
		std::cout << "[3] - zakoncz\n";
		
		std::cout << "Prosze wybrac numer: ";
		std::cin >> choice;
		
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		

		switch (choice)
		{
		case 1:
			Login(database, customer);
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

void Login(Database *database, User *customer)
{
	system("cls");
	// logujemy sie przez userID
	int user_ID;
	std::string password;

	std::cout << "Podaj login: ";
	std::cin >> user_ID;

	std::cout << "Podaj haslo: ";
	std::cin >> password;

	//sprawdzanie typu uzytkowania
	if (database->check_customer(user_ID))
	{
		customer = database->get_customer_data_by_id(user_ID);
		//check if account is accepted
		int check = database->check_account_aplication(user_ID);

		if (check !=1)
		{
			std::cout << "Poczekaj az administrator zaakaceptuje wniosek\n";
			system("pause");
			return;
		}

		//sprawdzenie hasla
		
		std::string encrypted_passeword = database->encrypt_password(password);
		std::string correct_password = database->get_user_password(user_ID);
		
		if (encrypted_passeword == correct_password) {
			customer->show_menu();
			return;
		}
		else {
			std::cout << "Nie poprawne haslo lub login\n";
			system("pause");
		}
		
	
	}
	else if(database->check_employe(user_ID))
	{
		customer = database->get_employee_data_by_id(user_ID);

		std::string encrypted_passeword = database->encrypt_password(password);
		std::string correct_password = database->get_employe_password(user_ID);

		if (encrypted_passeword == correct_password) {
			customer->show_menu();
			return;
		}
		else {
			std::cout << "Nie poprawne haslo lub login\n";
			system("pause");
		}
		
	}
	else if(database->check_admin(user_ID))
	{
		customer = database->get_admin_data_by_id(user_ID);

		std::string encrypted_passeword = database->encrypt_password(password);
		std::string correct_password = database->get_admin_password(user_ID);

		if (encrypted_passeword == correct_password) {
			customer->show_menu();
			return;
		}
		else {
			std::cout << "Nie poprawne haslo lub login\n";
			system("pause");
		}
		
	}
}

void Register(Database *database)
{
	int phonenumber = 0;
	std::string firstname, lastname, password, email, addres;
	std::regex email_pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
	std::regex phone_number_pattern(R"(\d{9})");

	std::cout << "Podaj Imie";
	std::cin >> firstname;

	std::cout << "Podaj Naziwsko";
	std::cin >> lastname;

	std::cin.ignore();
	std::cout << "Podaj Adres MIASTO ULICA NR BLOKU NR MIESZKANIA";
	std::getline(std::cin, addres);

	while (!std::regex_match(email, email_pattern))
	{
		std::cout << "Podaj email";
		std::cin >> email;
	}

	while (!std::regex_match(std::to_string(phonenumber), phone_number_pattern))
	{
		std::cout << "Podaj numer telefonu";
		std::cin >> phonenumber;
	}

	std::cout << "Podaj haslo";
	std::cin >> password;


	// to trzeba zmienić zeby wracało do login i wymagało logowania po zarejestrowaniu
	int user_id = database->generate_user_id();
	std::string encrypted_password = database->encrypt_password(password);
	database->create_user(user_id, firstname, lastname,  email, encrypted_password, phonenumber,addres);
	database->create_account(0, user_id);
	system("cls");
	std::cout << "Przeslano wniosek o zalozenie konta, prosimy poczekac na jego akceptacje \n";
	std::cout << "Pin do logowania: " << user_id << std::endl;
	system("pause");
	// pomysle pozniej nad lepszym sposobem przejscia do menu, odwolanie do funkcji main jest niedozwolone z programu (edit juz ogarniete)
}


