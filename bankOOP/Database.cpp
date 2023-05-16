#include "Database.h"


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

}

User* Database::get_admin_data_by_id(int user_id)
{

}

void Database::create_user(int user_id, std::string firstname, std::string lastname, std::string email, std::string password, int phonenumber)
{
    connect_database();

    std::string addres = "adres1";

    std::string query = "INSERT INTO customers (user_id, first_name, last_name,addres, email, password, phone_number) VALUES (?,?, ?, ?, ?, ?, ?)";

    con->setSchema("bank");
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
