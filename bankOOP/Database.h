#pragma once

#include <stdlib.h>
#include <iostream>
#include <vector>

#include "Customer.h"
#include "User.h"
#include "Account.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
class Database
{
protected:
    const std::string server = "tcp://127.0.0.1:3306"; // ip bazy danych
    const std::string username = "root"; // login
    const std::string password = ""; //haslo
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* res;
    //std::vector<Account*> accounts; //tablica przechowuj¹ca konta
    //std::vector<User*> users_data; // tablica przechowuj¹ca dane uzytkowników
    void connect_database()
    {
        try
        {
            driver = get_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException e)
        {
            std::cout << "Nie udalo sie polaczyc z baza danych. Error message: " << e.what() << std::endl;

        }
    }

public:

    void select_all_Accounts_from_database()
    {
        connect_database();
        con->setSchema("users");
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM klienci");
        while (res->next())
        {
            std::cout << res->getInt(1) << std::endl;
            std::cout << res->getString(2) << std::endl;
            std::cout << res->getString(3) << std::endl;

        }

        delete res;
        delete stmt;
        delete con;
    }

    void select_user_data(int user_id)
    {
        connect_database();
        std::string query = "SELECT * FROM klienci WHERE id='" + std::to_string(user_id)+"'";
        try
        {
            con->setSchema("users");
            stmt = con->createStatement();
            res = stmt->executeQuery(query);

            while (res->next()) 
            {
                std::cout << res->getInt(1) << std::endl;
                std::cout << res->getString(2) << std::endl;
                std::cout << res->getString(3) << std::endl;

            }
            std::cout << res->getString(3) << std::endl;
        }
        catch (...)
        {
            std::cout << "nie odnaleziono uzytkownika" << std::endl;
        }
        
        delete res;
        delete stmt;
        delete con;
    }

    /**
    * \brief Funkcja zwraca 0 jak znajdzie obiekt w bazie customers,1jak nie znajdzie
    * \param user_id
    * \return
    */

    int check_customer(int user_id)
    {
        connect_database();
        std::string query = "SELECT * FROM customers WHERE user_id='" + std::to_string(user_id) + "'";
        con->setSchema("test");
        stmt = con->createStatement();
        res = stmt->executeQuery(query);

        int result = 0; // Zmienna przechowuj¹ca wynik

        if (res->next())
        {
            // Znaleziono obiekt
            result = 0;
        }
        else
        {
            result = 1;
        }

        delete res;
        delete stmt;
        delete con;

        return result;
    }


    User* get_customer_data_by_id(int user_id)
    {
        connect_database();
        int userid;
        std::string firstname;
        std::string lastname;
        std::string email;
        std::string password;
        int phone_number;


        std::string query = "SELECT * FROM customers WHERE user_id='" + std::to_string(user_id) + "'";
        con->setSchema("users");
        stmt = con->createStatement();
        res = stmt->executeQuery(query);
        while (res->next())
        {
            userid = res->getInt(1);
            firstname = res->getString(2); 
            lastname = res->getString(3);
            email = res->getString(4);
            password = res->getString(5);
            phone_number = res->getInt(6);

            delete res;
            delete stmt;
            delete con;

            // tutaj bedzie utworzenie obiektu customer i zwrocenie go
            User *user = new Customer(0,userid,firstname,lastname,email,password,phone_number, 0);
            return user;
        }

    }

    

    
};

