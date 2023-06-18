#pragma once
#include "User.h"

class Client : public User
{
public:
	Client(const MyString& username, const MyString& password,
		const MyString& firstName, const MyString& lastName);
	Client(MyString&& username, MyString&& password,
		MyString&& firstName, MyString&& lastName);
	Client() = default;

	bool isClient() const;

	void saveToFile(std::ofstream& ofs) const override;
	void readFromFile(std::ifstream& ifs) override;
	//void print() const override;
};
