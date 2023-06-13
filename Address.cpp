#include "Address.h"

Address::Address(MyString&& name, int x, int y)
{
	_name = std::move(name);
	_x = x;
	_y = y;
}

Address::Address(MyString&& name, int x, int y, MyString&& description)
{
	_name = std::move(name);
	_description = std::move(description);
	_x = x;
	_y = y;
}

Address::Address(const MyString& name, int x, int y)
{
	_name = name;
	_x = x;
	_y = y;
}

Address::Address(const MyString& name, int x, int y, const MyString& description)
{
	_name = name;
	_description = description;
	_x = x;
	_y = y;
}



