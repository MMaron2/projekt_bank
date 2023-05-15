#pragma once
#include <iostream>
#include "Account.h"
class SavingAccount : public Account
{
public:
	SavingAccount(double balance_ = 0.0, int account_type_ = 0) :Account(balance_, account_type_)
	{

	}
	virtual void display_account() override;
};

