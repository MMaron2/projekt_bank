#pragma once
class Account
{
protected:
	double balance;
	int account_type;

public:
	Account(double = 0.0, int = 0);

	virtual void display_account() = 0; // funkcja wirtualna wyswietlaj¹ca dane konta
};

