#include "Customer.h"
#include "Database.h"
#include <iostream>
#include <cstdlib>


Customer::Customer(int user_id_, std::string first_name_, std::string last_name_, std::string email_, std::string password_, int phone_number_, int is_active_)
	: User(user_id_, first_name_, last_name_, email_, password_, phone_number_, is_active_)
{
	Database database;
	user_accounts = database.download_data_about_user_account(user_id_);
}

void Customer::show_menu()
{
	this->set_Active();
	system("cls");
	//tutaj Menu wlasciwe, przelewy itd
	int choice = 0;

	while (choice != 5)
	{
		std::cout << "[1] - przelewy\n";
		std::cout << "[2] - stan konta\n";
		std::cout << "[3] - wyswietl dane\n";
		std::cout << "[4] - wyswietl konta\n";
		std::cout << "[5] - wyloguj\n";
		try
		{
			std::cin >> choice;
		}
		catch (...)
		{
			std::cout << "wprowadzono zle dane\n";
			continue;
		}
		switch (choice)
		{
			case 1:
				break;
			case 2:
				break;
			case 3:
				Customer::show_user_data();
				break;
			case 4:
				show_accounts();
				break;
			case 5:
				return;
			default:
				break;
		}
	}
}

void Customer::create_user(User* customer)
{
	Database db;
}

void Customer::show_user_data()
{
	system("cls");
	std::cout << "id: " << this->user_id << std::endl;
	std::cout << "imie : " << this->first_name << std::endl;
	std::cout << "nazwisko: " << this->last_name << std::endl;
	std::cout << "email: " << this->email << std::endl;
	std::cout << "haslo: " << this->password << std::endl;
	std::cout << "nr telefonu: " << this->phone_number << std::endl;
	std::cout << "czy aktywny: " << this->is_active << std::endl;
}

void Customer::show_accounts()
{
	for (Account *account : user_accounts)
	{
		std::cout << "-------------konto----------------\n";
		account->display_account();
	}
}

void Customer::transfer_funds()
{

	Database database;
	int senders_account_number, receiving_account_number, transfer_ammount;
	std::cout << "---------Przelewy---------\n";
	std::cout << "Podaj numer konta z ktorego chesz przelac pieniadze: ";
	std::cin >> senders_account_number;
	std::cout << "Podaj numer konta na ktore chesz przelac pieniadze: ";
	std::cin >> receiving_account_number;
	std::cout << "Podaj kwote przelwu: ";
	std::cin >> transfer_ammount;


	database.update_user_balance(); // jeszcze trzeba dodaæ sprawdzenie ale to bêde sprawdza³ w bazie danych;

}


int Customer::show_user_id()
{
	return user_id;
}

void Customer::set_Active()
{
	this->is_active = 1;
}

std::string Customer::encrypt_password(std::string pass)
{
    std::string result = "";

    for (char c : pass) {
        if (isalpha(c)) {
            char shifted_c = toupper(c) + 1;
            if (shifted_c > 'Z') {
                shifted_c -= 26;
            }
            result += shifted_c;
        }
        else {
            result += c;
        }
    }
	return result;
}
