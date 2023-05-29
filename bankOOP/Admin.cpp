#include "Admin.h"
#include <iostream>
#include <iomanip>
#include "Database.h"

Admin::Admin(bool is_admin_, bool is_staff_, int user_id_, std::string first_name_, std::string last_name_, std::string email_, std::string password_, int phone_number_, int is_active_)
	:Employee(is_admin_, is_staff_, user_id_, first_name_, last_name_, email_, password_, phone_number_, is_active_){
}

void Admin::show_menu()
{
	system("cls");
	int choice = 0;

	while (choice != 6)
	{
		system("cls");
		std::cout << "[1] - Lista pracownikow\n";
		std::cout << "[2] - Usuwanie kont\n";
		std::cout << "[3] - Lista uztykownikow\n";
		std::cout << "[4] - Lista wnioskow o zalozenie konta\n";
		std::cout << "[5] - Dodanie konta pracownika\n";
		std::cout << "[6] - Wyloguj\n";

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
			employe_list();
			break;
		case 2:
			delete_customer_account();
			break;
		case 3:
			users_list();
			break;
		case 4:
			show_applications();
			break;
		case 5:
			create_employe_account();
			return;
		default:
			break;
		}
	}
}

void Admin::users_list()
{
	system("cls");
	Database database;
	std::vector<int> users_id;
	users_id = database.get_all_clients();

	
	const int idColumnWidth = 10;
	const int firstNameColumnWidth = 20;
	const int lastNameColumnWidth = 20;

	std::cout << std::left << std::setw(idColumnWidth) << "ID";
	std::cout << std::left << std::setw(firstNameColumnWidth) << "First Name";
	std::cout << std::left << std::setw(lastNameColumnWidth) << "Last Name";
	std::cout << std::endl;

	for (int i = 0; i < users_id.size(); ++i)
	{
		std::vector<std::string> users_credential;
		users_credential = database.get_user_credentials(users_id[i]);

		std::cout << std::left << std::setw(idColumnWidth) << users_id[i];
		std::cout << std::left << std::setw(firstNameColumnWidth) << users_credential[0];
		std::cout << std::left << std::setw(lastNameColumnWidth) << users_credential[1];
		std::cout << std::endl;
	}
	system("pause");
}

void Admin::delete_customer_account()
{
	system("cls");
	Database database;
	int usr_id;
	std::cout << "Prosze podac ID klienta do usuniecia";
	std::cin >> usr_id;

	database.delete_customer(usr_id);
	std::cout << "Uzytkownik zostal usuniety\n";
	
}


void Admin::create_employe_account()
{
	system("cls");
	Database database;
	std::string fname, lname, e_mail, pas;
	// podanie danych

	std::cout << "Podaj Imie";
	std::cin >> fname;

	std::cout << "Podaj Naziwsko";
	std::cin >> lname;

	std::cout << "Podaj email";
	std::cin >> e_mail;

	std::cout << "Podaj haslo";
	std::cin >> pas;

	std::string encrypted_password = database.encrypt_password(pas);
	int user_id = database.generate_user_id();
	database.create_employe(user_id, fname, lname, e_mail, encrypted_password);
	std::cout << "Utworzono konto pracownika jego ID " << user_id << std::endl;
	system("pause");

}

void Admin::employe_list()
{
	system("cls");
	Database database;
	std::vector<int> employe_ids;
	employe_ids = database.get_all_employe();

	// Ustalenie szerokoœci kolumn dla lepszego formatowania
	const int idColumnWidth = 15;
	const int firstNameColumnWidth = 20;
	const int lastNameColumnWidth = 20;

	std::cout << std::left << std::setw(idColumnWidth) << "Employee ID";
	std::cout << std::left << std::setw(firstNameColumnWidth) << "First Name";
	std::cout << std::left << std::setw(lastNameColumnWidth) << "Last Name";
	std::cout << std::endl;

	for (int i = 0; i < employe_ids.size(); ++i)
	{
		std::vector<std::string> employe_credentials;
		employe_credentials = database.get_employe_credentials(employe_ids[i]);

		std::cout << std::left << std::setw(idColumnWidth) << employe_ids[i];
		std::cout << std::left << std::setw(firstNameColumnWidth) << employe_credentials[0];
		std::cout << std::left << std::setw(lastNameColumnWidth) << employe_credentials[1];
		std::cout << std::endl;
	}
	system("pause");
}



