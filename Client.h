#pragma once
#include "User.h"

class Client : public User
{

	Client() = default;

	Client(const MyString& username, const MyString& password,
		const MyString& firstName, const MyString& lastName);
	Client(MyString&& username, MyString&& password,
		MyString&& firstName, MyString&& lastName);

	/*TODO void saveToFile(std::ofstream& ofs) const override;
	TODO void readFromFile(std::ifstream& ifs) override;
	TODO void print() const override;*/
};
