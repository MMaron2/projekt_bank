#include "User.h"
#include <iostream>
#include "Database.h"

User::User(int user_id_, std::string first_name_, std::string last_name_, std::string email_, std::string password_, int phone_number_)
{
	user_id = user_id_;
	first_name = first_name_;
	last_name = last_name_;
	email = email_;
	password = password_;
	phone_number = phone_number_;
}
