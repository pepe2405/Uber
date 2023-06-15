#include "User.h"

int User::currId = 1;

User::User(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName)
{
	this->id = currId;
	currId++;

	this->username = username;
	this->password = password;
	this->firstName = firstName;
	this->lastName = lastName;
}

User::User(MyString&& username, MyString&& password, MyString&& firstName, MyString&& lastName)
{
	this->id = currId;
	currId++;

	this->username = std::move(username);
	this->password = std::move(password);
	this->firstName = std::move(firstName);
	this->lastName = std::move(lastName);
}

void User::addMoney(double amount)
{
	this->balance += amount;
}

double User::getBalance() const
{
	return balance;
}

const MyString& User::getFirstName() const
{
	return firstName;
}

int User::getId() const
{
	return id;
}

const MyString& User::getLastName() const
{
	return lastName;
}

const MyString& User::getUsername() const
{
	return username;
}

bool User::isValidPassword(const MyString& password) const
{
	return this->password == password;
}









