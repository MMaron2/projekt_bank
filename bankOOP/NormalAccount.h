#pragma once
#include "Account.h"
#include <iostream>
class NormalAccount : public Account
{

public:
	NormalAccount(double balance_=0.0, int account_type_=0) : Account(balance_, account_type_)
	{

	}
	virtual void display_account() override;
};

