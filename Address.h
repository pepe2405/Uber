#pragma once
#include "MyString.h"

class Address
{
	MyString _name = "Unknown";
	MyString _description = "Unknown";
	int _x = 0;
	int _y = 0;

public:
	Address() = default;
	Address(const MyString& name, int x, int y, const MyString& description);
	Address(const MyString& name, int x, int y);
	Address(MyString&& name, int x, int y, MyString&& description);
	Address(MyString&& name, int x, int y);

	int getX() const;
	int getY() const;
};
