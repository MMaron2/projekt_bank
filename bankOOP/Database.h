#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Customer.h"
#include "User.h"
#include "Account.h"
#include "NormalAccount.h"
#include "SavingAccount.h"
#include "Transfer.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

class Database
{
private:
    const std::string server = "tcp://db4free.net:3306"; // ip bazy danych
    const std::string username = "fr3kz1"; // login
    const std::string password = "12345678"; //haslo
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
    int check_account_id(int account_id);
    //----------------------------------------------
    User* get_customer_data_by_id(int user_id); // zwraca wskaznik na obiekt typu User
    std::vector<Account*> download_data_about_user_account(int user_id); // zwraca tablicê zawieraj¹c¹ wskaŸniki na obiekty typu Account
    User* get_employee_data_by_id(int user_id);
    User* get_admin_data_by_id(int user_id);
    void create_user(int user_id, std::string firstname, std::string lastname, std::string email, std::string password, int phonenumber,std::string addres);
    int generate_user_id();
    int update_user_balance(); // funkcja do wywo³ania w Customer::transfer_founds aktualizuje bazê danych po wykonaniu przelewu (trzeba dodaæ deklaracje)
    std::string encrypt_password(std::string pass);
    std::vector<int> get_applications();
    std::vector<std::string> get_user_credentials(int user_id);
    std::vector<std::string> get_employe_credentials(int user_id);
    void accept_application(int user_id);
    int check_account_aplication(int user_id);
    void create_account(int type_, int user_id_);
    int generate_account_id();
    std::vector<int> get_all_clients();
    std::vector<int> get_all_employe();
    void delete_customer(int user_id);
    void create_employe(int user_id, std::string firstname, std::string lastname, std::string email, std::string password);
    void transfer_to_normalaccount(int account_id, double amount, int from_account_id);
    std::string get_user_password(int user_id);
    std::string get_employe_password(int user_id);
    std::string get_admin_password(int user_id);
    void add_transfer_to_database_transfer_history(int from_account_id, int to_account_id, double amount);
    std::vector<Transfer*> get_user_transfer_history(int account_id);
    void revaluation_of_the_savings_account(int user_id);
};

