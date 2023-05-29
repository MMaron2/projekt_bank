#include "Database.h"
#include "Employee.h"
#include <string>
#include <time.h>

#include "Admin.h"

void Database::connect_database()
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

int Database::check_customer(int user_id)
{
    connect_database();
    std::string query = "SELECT * FROM customers WHERE user_id='" + std::to_string(user_id) + "'";
    con->setSchema("bankoop");
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

    delete this->res;
    delete this->stmt;
    delete this->con;

    return result;
}

int Database::check_employe(int user_id)
{
    connect_database();
    std::string query = "SELECT * FROM employe WHERE user_id='" + std::to_string(user_id) + "'";
    con->setSchema("bankoop");
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

    delete this->res;
    delete this->stmt;
    delete this->con;

    return result;
}

int Database::check_admin(int user_id)
{
    connect_database();
    std::string query = "SELECT * FROM admin WHERE user_id='" + std::to_string(user_id) + "'";
    con->setSchema("bankoop");
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

    delete this->res;
    delete this->stmt;
    delete this->con;

    return result;
}

int Database::check_account_id(int account_id)
{
    connect_database();
    std::string query = "SELECT * FROM accounts WHERE account_id='" + std::to_string(account_id) + "'";
    con->setSchema("bankoop");
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

User* Database::get_customer_data_by_id(int user_id)
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
    con->setSchema("bankoop");
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

        delete this->res;
        delete this->stmt;
        delete this->con;

        // tutaj bedzie utworzenie obiektu customer i zwrocenie go
        User* user = new Customer(userid, firstname, lastname, email, password, phone_number, 0);
        return user;
    }
}

User* Database::get_employee_data_by_id(int user_id)
{
    connect_database();
    int userid;
    std::string firstname;
    std::string lastname;
    std::string email;
    std::string password;
    int is_Admin;
    int phone_number;


    std::string query = "SELECT * FROM employe WHERE user_id='" + std::to_string(user_id) + "'";
    con->setSchema("bankoop");
    stmt = con->createStatement();
    res = stmt->executeQuery(query);
    while (res->next())
    {
        userid = res->getInt(1);
        firstname = res->getString(2);
        lastname = res->getString(3);
    	is_Admin = res->getInt(4);
        email = res->getString(5);
        password = res->getString(6);

        delete this->res;
        delete this->stmt;
        delete this->con;

        User* user = new Employee(false,true,user_id,firstname,lastname,email,password,0,0);
        return user;
    }
}

User* Database::get_admin_data_by_id(int user_id)
{
    connect_database();
    int userid;
    std::string firstname;
    std::string lastname;
    std::string email;
    std::string password;



    std::string query = "SELECT * FROM admin WHERE user_id='" + std::to_string(user_id) + "'";
    con->setSchema("bankoop");
    stmt = con->createStatement();
    res = stmt->executeQuery(query);
    while (res->next())
    {
        userid = res->getInt(1);
        firstname = res->getString(2);
        lastname = res->getString(3);
        email = res->getString(4);
        password = res->getString(5);

        delete this->res;
        delete this->stmt;
        delete this->con;

        User* admin = new Admin(true, true, user_id, firstname, lastname, email, password, 0, 0);
        return admin;
    }
}

void Database::create_user(int user_id, std::string firstname, std::string lastname, std::string email, std::string password, int phonenumber, std::string adres)
{
    connect_database();

    // tworzenie w bazie nowego uzytkownika
    std::string query = "INSERT INTO customers (user_id, first_name, last_name,addres, email, password, phone_number, is_accepted) VALUES (?,?, ?, ?, ?, ?, ?, ?)";
    con->setSchema("bankoop");
    pstmt = con->prepareStatement(query);
    pstmt->setInt(1, user_id);
    pstmt->setString(2, firstname);
    pstmt->setString(3, lastname);
    pstmt->setString(4, adres);
    pstmt->setString(5, email);
    pstmt->setString(6, password);
    pstmt->setInt(7, phonenumber);
    pstmt->setInt(8, 0);
    pstmt->executeUpdate();

    con->close();
    delete con;
    delete pstmt;
}

std::vector<Account*> Database::download_data_about_user_account(int user_id)
{
    std::vector<Account*> accounts;
    Account* account;

    int account_id_;
    double balance_;
    int account_type_;

    connect_database();

    std::string query = "SELECT account_id, balance, account_type FROM accounts WHERE user_id='" + std::to_string(user_id) + "'";
    con->setSchema("bankoop");
    stmt = con->createStatement();
    res = stmt->executeQuery(query);

        if (res->next())
        {
            res->previous();
            while (res->next())
            {

                account_id_ = res->getInt(1);
                balance_ = res->getDouble(2);
                account_type_ = res->getInt(3);

                if (account_type_ == 0)
                {
                    account = new NormalAccount(account_id_, balance_, account_type_);
                    accounts.push_back(account);
                }
                else if (account_type_ == 1)
                {
                    account = new SavingAccount(account_id_, balance_, account_type_);
                    accounts.push_back(account);
                }
            }
        }
        else
        {
            return accounts;
        }
    delete res;
    delete stmt;
    delete con;

    return accounts;
}

int Database::generate_user_id()
{
    int user_id;
    srand(time(NULL));
    do
    {

        user_id = rand() % 999999 + 100000;

    } while (check_customer(user_id) && check_employe(user_id) && check_admin(user_id));

    return user_id;
}

int Database::update_user_balance()
{
    return 0;
}

std::string Database::encrypt_password(std::string pass)
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

std::vector<int> Database::get_applications()
{
    connect_database();

    std::vector<int> users_id;
    std::string query = "SELECT user_id FROM customers WHERE is_accepted = 0";
    con->setSchema("bankoop");
    stmt = con->createStatement();
    res = stmt->executeQuery(query);
    while (res->next())
    {
        users_id.push_back(res->getInt(1));
    }

    delete this->res;
    delete this->stmt;
    delete this->con;

    return users_id;

}

//co to robi ? zwraca dane uzytkownika ktory zlozyl wniosek i employe go rozpatrza
std::vector<std::string> Database::get_user_credentials(int user_id)
{
    //w formacie 0 first name 1 last name 2 addres  3 email 4 phone number
    std::vector<std::string> users_credential;
    connect_database();
    int userid;
    std::string firstname;
    std::string lastname;
    std::string email;
    std::string password;
    std::string addres;
    int phone_number;


    std::string query = "SELECT * FROM customers WHERE user_id='" + std::to_string(user_id) + "'";
    con->setSchema("bankoop");
    stmt = con->createStatement();
    res = stmt->executeQuery(query);
    while (res->next())
    {
        firstname = res->getString(2);
        lastname = res->getString(3);
        addres = res->getString(4);
        email = res->getString(5);
        phone_number = res->getInt(7);

        delete this->res;
        delete this->stmt;
        delete this->con;

        users_credential.push_back(firstname);
        users_credential.push_back(lastname);
        users_credential.push_back(addres);
        users_credential.push_back(email);
        users_credential.push_back(std::to_string(phone_number));

        return users_credential;
        
    }
}

void Database::accept_application(int user_id)
{
    connect_database();

    std::string query = "UPDATE customers SET is_accepted = 1 WHERE  user_id='" + std::to_string(user_id) + "'";

    con->setSchema("bankoop");
    pstmt = con->prepareStatement(query);
    pstmt->executeUpdate();

    delete this->con;
    delete this->pstmt;
}

int Database::check_account_aplication(int user_id)
{
    connect_database();
    std::string query = "SELECT is_accepted FROM customers WHERE user_id='" + std::to_string(user_id) + "'";
    con->setSchema("bankoop");
    stmt = con->createStatement();
    res = stmt->executeQuery(query);

    int result = 0; // Zmienna przechowująca wynik

    while (res->next())
    {
        result = res->getInt(1);
    }

    delete this->res;
    delete this->stmt;
    delete this->con;

    return result;

}

void Database::create_account(int type_, int user_id_)
{
    connect_database();
    try
    {
        int account_id = this->generate_account_id();
        std::string query = "INSERT INTO accounts (account_id, user_id, balance, account_type) VALUES (?,?,?,?)";
        con->setSchema("bankoop");
        pstmt = con->prepareStatement(query);
        pstmt->setInt(1, account_id);
        pstmt->setInt(2, user_id_);
        pstmt->setDouble(3, 0);
        pstmt->setInt(4, type_);
        pstmt->executeUpdate();
    }
    catch (sql::SQLException e)
    {
        std::cout << "Nie udalo sie polaczyc z baza danych. Error message: " << e.what() << std::endl;
    }

    delete con;
    delete pstmt;
}

int Database::generate_account_id()
{
    int account_id;
    srand(time(NULL));
    account_id = rand() % 99999999 + 10000000;
    return account_id;
}

std::vector<int> Database::get_all_clients()
{
    connect_database();
    std::vector<int> users_id;
    std::string query = "SELECT user_id FROM customers";

    con->setSchema("bankoop");
    stmt = con->createStatement();
    res = stmt->executeQuery(query);

    while (res->next())
    {
        users_id.push_back(res->getInt(1));
    }
    return users_id;

}

std::vector<int> Database::get_all_employe()
{
    connect_database();
    std::vector<int> users_id;
    std::string query = "SELECT user_id FROM employe";

    con->setSchema("bankoop");
    stmt = con->createStatement();
    res = stmt->executeQuery(query);

    while (res->next())
    {
        users_id.push_back(res->getInt(1));
    }
    delete con;
    delete stmt;
    delete res;
    return users_id;

}

void Database::delete_customer(int user_id)
{
    connect_database();

    std::string query = "DELETE FROM customers WHERE user_id = '" + std::to_string(user_id) + "'";

    try {
        con->setSchema("bankoop");
        stmt = con->createStatement();
        res = stmt->executeQuery(query);

        delete con;
        delete stmt;
        delete res;
    }
    catch (sql::SQLException& e) {

    }

}

void Database::create_employe(int user_id, std::string firstname, std::string lastname, std::string email, std::string password)
{
    connect_database();
    // Tworzenie w bazie nowego użytkownika
    std::string query = "INSERT INTO employe (user_id, firstname, lastname,isAdmin, email, password) VALUES (?, ?,?, ?, ?, ?)";
    con->setSchema("bankoop");
    pstmt = con->prepareStatement(query);
    pstmt->setInt(1, user_id);
    pstmt->setString(2, firstname);
    pstmt->setString(3, lastname);
    pstmt->setInt(4,0);
    pstmt->setString(5, email);
    pstmt->setString(6, password);
    pstmt->executeUpdate();

    con->close();
    delete con;
    delete pstmt;
}

std::vector<std::string> Database::get_employe_credentials(int user_id)
{
    //w formacie 0 first name 1 last name
    std::vector<std::string> users_credential;
    connect_database();
    int userid;
    std::string firstname;
    std::string lastname;



    std::string query = "SELECT * FROM employe WHERE user_id='" + std::to_string(user_id) + "'";
    con->setSchema("bankoop");
    stmt = con->createStatement();
    res = stmt->executeQuery(query);
    while (res->next())
    {
        firstname = res->getString(2);
        lastname = res->getString(3);

        delete this->res;
        delete this->stmt;
        delete this->con;

        users_credential.push_back(firstname);
        users_credential.push_back(lastname);

        return users_credential;
        
    }
}

void Database::transfer_to_normalaccount(int account_id, double amount, int from_account_id)
{
    connect_database();
    con->setSchema("bankoop");
    std::string query = "UPDATE accounts SET balance= balance + ? WHERE account_id=?";
    pstmt = con->prepareStatement(query);
	pstmt->setDouble(1, amount);
    pstmt->setInt(2 , account_id);
    pstmt->execute();
    query = "UPDATE accounts SET balance= balance - ? WHERE account_id=?";
    pstmt = con->prepareStatement(query);
    pstmt->setDouble(1, amount);
    pstmt->setInt(2, from_account_id);
    pstmt->execute();
}

std::string Database::get_user_password(int user_id) {
    connect_database();
    std::string password;
  

    std::string query = "SELECT * FROM customers WHERE user_id='" + std::to_string(user_id) + "'";
    con->setSchema("bankoop");
    stmt = con->createStatement();
    res = stmt->executeQuery(query);
    while (res->next())
    {
        password = res->getString(6);

        delete this->res;
        delete this->stmt;
        delete this->con;
        return password;
    }
   
}

std::string Database::get_employe_password(int user_id) {
    connect_database();
    std::string password;


    std::string query = "SELECT * FROM employe WHERE user_id='" + std::to_string(user_id) + "'";
    con->setSchema("bankoop");
    stmt = con->createStatement();
    res = stmt->executeQuery(query);
    while (res->next())
    {
        password = res->getString(6);

        delete this->res;
        delete this->stmt;
        delete this->con;
        return password;
    }

}

std::string Database::get_admin_password(int user_id) {
    connect_database();
    std::string password;


    std::string query = "SELECT * FROM admin WHERE user_id='" + std::to_string(user_id) + "'";
    con->setSchema("bankoop");
    stmt = con->createStatement();
    res = stmt->executeQuery(query);
    while (res->next())
    {
        password = res->getString(6);

        delete this->res;
        delete this->stmt;
        delete this->con;
        return password;
    }

}

void Database::add_transfer_to_database_transfer_history(int from_account_id, int to_account_id, double amount)
{
    connect_database();
    // Tworzenie w bazie nowego użytkownika
    std::string query = "INSERT INTO history (account_id_1, account_id_2, amount) VALUES (?,?,?)";
    con->setSchema("bankoop");
    pstmt = con->prepareStatement(query);
    pstmt->setInt(1, from_account_id);
    pstmt->setInt(2, to_account_id);
    pstmt->setDouble(3, amount);
    pstmt->execute();

    con->close();
    delete con;
    delete pstmt;
}

std::vector<Transfer*> Database::get_user_transfer_history(int account_id)
{
    std::vector<Transfer*> transfers;
    Transfer* transfer;
    connect_database();
    int id, from_account_id, to_account_id;
    double amount;
    std::string date;

    std::string query = "SELECT * FROM history WHERE account_id_1='" + std::to_string(account_id) + "'" + "OR account_id_2='" + std::to_string(account_id)+"'";
    con->setSchema("bankoop");
    stmt = con->createStatement();
    res = stmt->executeQuery(query);
    while (res->next())
    {
        id = res->getInt(1);
        from_account_id = res->getInt(2);
        to_account_id = res->getInt(3);
        amount = res->getDouble(4);
        date = res->getString(5);

        transfer = new Transfer(id, from_account_id, to_account_id, amount, date);
        transfers.push_back(transfer);
    }
    con->close();
    delete this->res;
    delete this->stmt;
    delete this->con;

    return transfers;

}

void Database::revaluation_of_the_savings_account(int user_id)
{
    connect_database();
    con->setSchema("bankoop");
    std::string query = "UPDATE accounts SET balance= ROUND(balance + (balance * 0.10), 2) WHERE user_id ='"+ std::to_string(user_id) + "' AND account_type = 1";
    pstmt = con->prepareStatement(query);
    pstmt->execute();
}


