#pragma once
#include <iostream>
#include "Customer.h"
class Transfer
{
	friend class Customer;
private:
	int id;
	int from_account_id;
	int to_account_id;
	double amount;
	std::string date;
public:
	Transfer(int, int, int, double, std::string);
};

