#include "Database.h"
#include "Employee.h"

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
    con->setSchema("bank");
    stmt = con->createStatement();
    res = stmt->executeQuery(query);

    int result = 0; // Zmienna przechowująca wynik

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

int Database::check_employe(int user_id)
{
    connect_database();
    std::string query = "SELECT * FROM employe WHERE user_id='" + std::to_string(user_id) + "'";
    con->setSchema("bank");
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

int Database::check_admin(int user_id)
{
    connect_database();
    std::string query = "SELECT * FROM admin WHERE user_id='" + std::to_string(user_id) + "'";
    con->setSchema("bank");
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
    con->setSchema("bank");
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
    con->setSchema("bank");
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

        delete res;
        delete stmt;
        delete con;

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
    int is_Admin;
    int phone_number;


    std::string query = "SELECT * FROM admin WHERE user_id='" + std::to_string(user_id) + "'";
    con->setSchema("bank");
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

        delete res;
        delete stmt;
        delete con;

        User* user = new Employee(true, true, user_id, firstname, lastname, email, password, 0, 0);
        return user;
    }
}

void Database::create_user(int user_id, std::string firstname, std::string lastname, std::string email, std::string password, int phonenumber, std::string adres)
{
    connect_database();

    std::string query = "INSERT INTO customers (user_id, first_name, last_name,addres, email, password, phone_number) VALUES (?,?, ?, ?, ?, ?, ?)";

    con->setSchema("bank");
    pstmt = con->prepareStatement(query);
    pstmt->setInt(1, user_id);
    pstmt->setString(2, firstname);
    pstmt->setString(3, lastname);
    pstmt->setString(4, adres);
    pstmt->setString(5, email);
    pstmt->setString(6, password);
    pstmt->setInt(7, phonenumber);
    pstmt->executeUpdate();

    delete con;
    delete pstmt;
}

std::vector<Account*> Database::download_data_about_user_account(int user_id)
{
    std::vector<Account*> accounts;
    Account* account;

    connect_database();
    int account_id_;
    double balance_;
    int account_type_;

    std::string query = "SELECT * FROM accounts WHERE user_id='" + std::to_string(user_id) + "'";
    con->setSchema("bank");
    stmt = con->createStatement();
    res = stmt->executeQuery(query);

    try
    {
        if (res->next())
        {
            while (res->next())
            {

                account_id_ = res->getInt(3);
                balance_ = res->getDouble(4);
                account_type_ = res->getInt(5);

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
    }
    catch (...) {
        std::cout << "nie udalo sie pobrac kont\n";
    }
    delete res;
    delete stmt;
    delete con;

    return accounts;
}

int Database::rand_id()
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

int Database::generate_user_id()
{
    int id = rand_id();

    int customer_id = check_customer(id);
    int employe_id = check_employe(id);

    if (customer_id == 0)
    {
        if (employe_id == 0)
        {
            return id;
        }
    }
    else
    {
        //pozniej ogarne zeby to zoptymalizowac
    }
    return id;
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
    con->setSchema("bank");
    stmt = con->createStatement();
    res = stmt->executeQuery(query);
    while (res->next())
    {
        users_id.push_back(res->getInt(1));
    }

    delete res;
    delete stmt;
    delete con;

    return users_id;

}

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
    con->setSchema("bank");
    stmt = con->createStatement();
    res = stmt->executeQuery(query);
    while (res->next())
    {
        firstname = res->getString(2);
        lastname = res->getString(3);
        addres = res->getString(4);
        email = res->getString(5);
        phone_number = res->getInt(7);

        delete res;
        delete stmt;
        delete con;

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

    con->setSchema("bank");
    pstmt = con->prepareStatement(query);
    pstmt->executeUpdate();

    delete con;
    delete pstmt;
}

int Database::check_account_aplication(int user_id)
{
    connect_database();
    std::string query = "SELECT is_accepted FROM customers WHERE user_id='" + std::to_string(user_id) + "'";
    con->setSchema("bank");
    stmt = con->createStatement();
    res = stmt->executeQuery(query);

    int result; // Zmienna przechowująca wynik

    while (res->next())
    {
        result = res->getInt(1);
    }

    delete res;
    delete stmt;
    delete con;

    return result;

}
