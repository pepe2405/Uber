#include "Client.h"

Client::Client(MyString&& username, MyString&& password, MyString&& firstName, MyString&& lastName)
	:User(std::move(username), std::move(password), std::move(firstName), std::move(lastName)) {}

Client::Client(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName)
	:User(username, password, firstName, lastName) {}

