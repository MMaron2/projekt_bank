#include "Employee.h"
#include <iostream>
#include "Database.h"
#include "User.h"
#include "Customer.h"

Employee::Employee(bool is_admin_, bool is_staff_, int user_id_, std::string first_name_, std::string last_name_, std::string email_, std::string password_, int phone_number_, int is_active_)
	:User(user_id_, first_name_, last_name_, email_, password_, phone_number_ ,is_active_)
{
	is_admin = is_admin_;
	is_staff = is_staff_;
}

void Employee::show_menu()
{
	system("cls");
	int choice = 0;

	while (choice != 3)
	{
		std::cout << "[1] - Wnioski do akceptacji\n";
		std::cout << "[2] - Wyswietl uzytkownika\n";
		std::cout << "[3] - Lista uztykownikow\n";
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
			show_applications();
			break;
		case 2:
			break;
		case 3:
			
			break;
		case 4:
			
			break;
		case 5:
			return;
		default:
			break;
		}
	}
}

void Employee::show_applications()
{
	Database database;
	std::vector<int> users_id;
	int usr_id;

	users_id = database.get_applications();

	std::cout << "Witaj (nazwa pracownika). Masz " << users_id.size() << " wnioskow do sprawdzenia. Wpisz [0] zeby sie cofnac, [1] aby sprawdzic" << std::endl;

	std::cout << "Lista id wnioskow" << std::endl;
	for (int i = 0; i < users_id.size(); ++i)
	{
		std::cout << users_id[i] << std::endl;
	}

	std::cout << "Wpisz id aby rozpatrzyc wniosek" << std::endl;
	std::cin >> usr_id;

	show_application(usr_id);


}

void Employee::show_application(int user_id)
{
	system("cls");
	int c;
	Database database;
	std::vector<std::string> credentials;
	credentials = database.get_user_credentials(user_id);

	// Todo ladniejsze wyswietlenie tego
	std::cout << credentials[0] << std::endl;
	std::cout << credentials[1] << std::endl;
	std::cout << credentials[2] << std::endl;
	std::cout << credentials[3] << std::endl;

	std::cout << "[0] Akceptacja [1] Odrzucenie";
	std::cin >> c;

	if (c == 0)
	{
		database.accept_application(user_id);
	}else
	{
		std::cout << "Odrzucono";
	}

}
