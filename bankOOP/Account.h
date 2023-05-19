#pragma once
#include "Customer.h";
class Account
{
protected:
	int account_id;
	double balance;
	int account_type;
	friend class Customer;

public:
	Account(int, double, int);

	void transfer_founds()
	{
			
	}

	virtual void display_account() = 0; // funkcja wirtualna wyswietlaj¹ca dane konta
	virtual void display_account_type() = 0;
	virtual void show_balance() = 0;
};

