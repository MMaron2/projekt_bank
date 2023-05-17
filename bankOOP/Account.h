#pragma once
class Account
{
protected:
	int account_id;
	double balance;
	int account_type;

public:
	Account(int, double, int);

	virtual void display_account() = 0; // funkcja wirtualna wyswietlaj¹ca dane konta
	virtual void display_account_type() = 0;
};

