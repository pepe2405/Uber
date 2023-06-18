#include "Driver.h"

#include <fstream>

Driver::Driver(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName, const MyString& carPlate, const MyString& phone)
	:User(username, password, firstName, lastName)
{
	this->carPlate = carPlate;
	this->phone = phone;
}

Driver::Driver(MyString&& username, MyString&& password, MyString&& firstName, MyString&& lastName, MyString&& carPlate, MyString&& phone)
	:User(username, password, firstName, lastName)
{
	this->carPlate = std::move(carPlate);
	this->phone = std::move(phone);
}

const Address& Driver::getAddress() const
{
	return this->address;
}

void Driver::setAddress(Address&& address)
{
	this->address = std::move(address);
}

void Driver::setAddress(const Address& address)
{
	this->address = address;
}

void Driver::rate(double newRating)
{
	ratingSum += newRating;
	ratingCount++;
	rating = ratingSum / ratingCount;
}

bool Driver::isClient() const
{
	return false;
}

bool Driver::isFree() const
{
	return free;
}

void Driver::setFree(bool el)
{
	free = el;
}

void Driver::saveToFile(std::ofstream& ofs) const
{
	User::saveToFile(ofs);
	ofs.write((const char*)&rating, sizeof rating);
	carPlate.saveToFile(ofs);
	phone.saveToFile(ofs);
	address.saveToFile(ofs);
	ofs.write((const char*)&ratingCount, sizeof ratingCount);
	ofs.write((const char*)&ratingSum, sizeof ratingSum);
}

void Driver::readFromFile(std::ifstream& ifs)
{
	User::readFromFile(ifs);
	ifs.read((char*)&rating, sizeof rating);
	carPlate.readFromFile(ifs);
	phone.readFromFile(ifs);
	address.readFromFile(ifs);
	ifs.read((char*)&ratingCount, sizeof ratingCount);
	ifs.read((char*)&ratingSum, sizeof ratingSum);
}



