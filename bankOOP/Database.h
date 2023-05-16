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
private:
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
            result = 1;
        }
        else
        {
            result = 0;
        }

        delete res;
        delete stmt;
        delete con;

        return result;
    }

    int check_employe(int user_id)
    {
        connect_database();
        std::string query = "SELECT * FROM employe WHERE user_id='" + std::to_string(user_id) + "'";
        con->setSchema("test");
        stmt = con->createStatement();
        res = stmt->executeQuery(query);

        int result = 0;

        if (res->next())
        {
            // Znaleziono obiekt
            result = 1;
        }
        else
        {
            result = 0;
        }

        delete res;
        delete stmt;
        delete con;

        return result;

    }

    int check_admin(int user_id)
    {
        connect_database();
        std::string query = "SELECT * FROM admin WHERE user_id='" + std::to_string(user_id) + "'";
        con->setSchema("test");
        stmt = con->createStatement();
        res = stmt->executeQuery(query);

        int result = 0;

        if (res->next())
        {
            // Znaleziono obiekt
            result = 1;
        }
        else
        {
            result = 0;
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
       // std::string addres;
        int phone_number;


        std::string query = "SELECT * FROM customers WHERE user_id='" + std::to_string(user_id) + "'";
        con->setSchema("test");
        stmt = con->createStatement();
        res = stmt->executeQuery(query);
        while (res->next())
        {
            userid = res->getInt(1);
            firstname = res->getString(2); 
            lastname = res->getString(3);
          //  addres = res->getString(4);
            email = res->getString(5);
            password = res->getString(6);
            phone_number = res->getInt(7);

            delete res;
            delete stmt;
            delete con;

            // tutaj bedzie utworzenie obiektu customer i zwrocenie go
            User *user = new Customer(userid,firstname,lastname,email,password,phone_number, 0);
            return user;
        }

    }

    User* get_employee_data_by_id(int user_id)
    {

    }

    User* get_admin_data_by_id(int user_id)
    {

    }

    void create_user(int user_id, std::string firstname, std::string lastname, std::string email, std::string password, int phonenumber)
    {
        connect_database();
        
        std::string addres = "adres1";

        std::string query = "INSERT INTO customers (user_id, first_name, last_name,addres, email, password, phone_number) VALUES (?,?, ?, ?, ?, ?, ?)";

        con->setSchema("test");
        pstmt = con->prepareStatement(query);
        pstmt->setInt(1, user_id);
        pstmt->setString(2, firstname);
        pstmt->setString(3, lastname);
        pstmt->setString(4, addres);
        pstmt->setString(5, email);
        pstmt->setString(6, password);
        pstmt->setInt(7, phonenumber);
        pstmt->executeUpdate();

        delete con;
        delete pstmt;
    }

    int rand_id()
    {
        srand(time(NULL));
        int id_ = 0;
        int id = 0;
        for (int i = 0; i < 6; ++i)
        {
            id_ = rand();
            id += id_;

        }
        return id;
    }

    int generate_user_id()
    {
        int id = rand_id();

        int customer_id = check_customer(id);
        int employe_id = check_employe(id);

        if (customer_id == 0)
        {
	        if(employe_id == 0)
	        {
                return id;
	        }
        }else
        {
	       //pozniej ogarne zeby to zoptymalizowac
        }
        return id;
    }
};

