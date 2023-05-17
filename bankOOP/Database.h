#pragma once

#include <stdlib.h>
#include <iostream>
#include <vector>


#include "Customer.h"
#include "User.h"
#include "Account.h"
#include "NormalAccount.h"
#include "SavingAccount.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
class Database
{
private:
    const std::string server = "tcp://127.0.0.1:3306"; // ip bazy danych
    const std::string username = "root"; // login
    const std::string password = ""; //haslo
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* res;

    void connect_database();

public:

    /**
    * \brief Funkcja zwraca 0 jak znajdzie obiekt w bazie customers,1jak nie znajdzie
    * \param user_id
    * \return
    */
    int check_customer(int user_id);
    int check_employe(int user_id);
    int check_admin(int user_id);
    //----------------------------------------------
    User* get_customer_data_by_id(int user_id); // zwraca wskaznik na obiekt typu User
    std::vector<Account*> download_data_about_user_account(int user_id); // zwraca tablicê zawieraj¹c¹ wskaŸniki na obiekty typu Account
    User* get_employee_data_by_id(int user_id);
    User* get_admin_data_by_id(int user_id);
    void create_user(int user_id, std::string firstname, std::string lastname, std::string email, std::string password, int phonenumber);
    int rand_id();
    int generate_user_id();
    int update_user_balance(); // funkcja do wywo³ania w Customer::transfer_founds aktualizuje bazê danych po wykonaniu przelewu (trzeba dodaæ deklaracje)
    std::string encrypt_password(std::string pass);
    
};

