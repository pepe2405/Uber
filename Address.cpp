#include "Address.h"

#include <fstream>

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

int Address::getX() const
{
	return _x;
}

int Address::getY() const
{
	return _y;
}

const MyString& Address::getName() const
{
	return _name;
}

const MyString& Address::getDescr() const
{
	return _description;
}

void Address::saveToFile(std::ofstream& ofs) const
{
	_name.saveToFile(ofs);
	ofs.write((const char*)&this->_x, sizeof _x);
	ofs.write((const char*)&this->_y, sizeof _y);
	_description.saveToFile(ofs);
}

void Address::readFromFile(std::ifstream& ifs)
{
	_name.readFromFile(ifs);
	ifs.read((char*)&this->_x, sizeof _x);
	ifs.read((char*)&this->_y, sizeof _y);
	_description.readFromFile(ifs);
}
