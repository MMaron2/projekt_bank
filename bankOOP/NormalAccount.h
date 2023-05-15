#pragma once
#include "Account.h"
#include <iostream>
class NormalAccount : public Account
{

public:
	NormalAccount(int account_id_ = 0, double balance_=0.0, int account_type_=0) : Account(account_id_, balance_, account_type_)
	{

	}
	virtual void display_account() override;
	virtual void display_account_type() override;
};

