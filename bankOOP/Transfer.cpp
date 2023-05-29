#include "Transfer.h"

Transfer::Transfer(int id_, int from_account_id_, int to_account_id_, double amount_, std::string date_)
{
	id = id_;
	from_account_id = from_account_id_;
	to_account_id = to_account_id_;
	amount = amount_;
	date = date_;
}
