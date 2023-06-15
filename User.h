#pragma once
#include "MyString.h"

class User
{
	static int currId;

	int id = 0;
	MyString username;
	MyString password;

	MyString firstName;
	MyString lastName;
	double balance = 0;

protected:
	User() = delete;
	User(const MyString& username, const MyString& password,
		const MyString& firstName, const MyString& lastName);
	User(MyString&& username, MyString&& password,
		MyString&& firstName, MyString&& lastName);

public:
	int getId() const;
	const MyString& getUsername() const;
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	double getBalance() const;
	void addMoney(double amount);

	bool isValidPassword(const MyString& password) const;

	/*TODO: virtual void saveToFile(std::ofstream& ofs) const;
	TODO: virtual void readFromFile(std::ifstream& ifs);*/
	virtual void print() const = 0;

	virtual bool isClient() const = 0;

	virtual ~User() = default;
};
