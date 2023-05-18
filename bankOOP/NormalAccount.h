#pragma once
#include "Account.h"
#include <iostream>
class NormalAccount : public Account
{

public:
	NormalAccount(int account_id_, double balance_, int account_type_) : Account(account_id_, balance_, account_type_)
	{

	}
	virtual void display_account() override;
	virtual void display_account_type() override;
	virtual void show_balance() override;
};

