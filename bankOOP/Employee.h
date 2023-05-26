#pragma once
#include "User.h"
class Employee :public User
{
protected:
	bool is_admin;
	bool is_staff;

public:
	Employee(bool, bool, int, std::string, std::string, std::string, std::string, int, int); // konstruktor
	virtual void show_menu() override; // funkcja wirtualna wyswietlaj¹ca inter
	void show_applications();
	void show_application(int user_id);
	void users_list();
	void show_user_details();
};

