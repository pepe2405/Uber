#pragma once
#include "Address.h"
#include "User.h"

class Driver : public User
{
	double rating = 0;
	MyString carPlate;
	MyString phone;
	Address address = { "Unknown", 0, 0, "" };
	int ratingCount = 0;
	double ratingSum = 0;
	bool isHeFree = true;

public:
	Driver(const MyString& username, const MyString& password,
		const MyString& firstName, const MyString& lastName,
		const MyString& carPlate, const MyString& phone);
	Driver(MyString&& username, MyString&& password,
		MyString&& firstName, MyString&& lastName,
		MyString&& carPlate, MyString&& phone);

	const Address& getAddress() const;
	void setAddress(const Address& address);
	void setAddress(Address&& address);

	void setFreedom(bool free);
	bool isFree() const;

	void rate(double newRating);

	bool isClient() const override;

	void print() const override;
};
