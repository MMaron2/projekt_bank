#pragma once

#include <stdlib.h>
#include <iostream>
#include <vector>

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

public:
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

    void select_all_Accounts_from_database()
    {
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

    

    
};

