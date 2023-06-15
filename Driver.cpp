#include "Driver.h"

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

void Driver::setFreedom(bool free)
{
	isHeFree = free;
}

bool Driver::isFree() const
{
	return isHeFree;
}


