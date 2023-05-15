#pragma once
class Account
{
protected:
	int account_id;
	double balance;
	int account_type;

public:
	Account(int = 0, double = 0.0, int = 0);

	virtual void display_account() = 0; // funkcja wirtualna wyswietlaj¹ca dane konta
};

