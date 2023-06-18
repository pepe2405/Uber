#include "RegDriverCommand.h"

void RegDriverCommand::execute(Application* app)
{
	try
	{
		MyString username, password, firstName, lastName, carNumber, phoneNumber;
		std::cout << "Input username: ";
		std::cin >> username;
		std::cout << "Input password: ";
		std::cin >> password;
		std::cout << "Input first name: ";
		std::cin >> firstName;
		std::cout << "Input last name: ";
		std::cin >> lastName;
		std::cout << "Input car number: ";
		std::cin >> carNumber;
		std::cout << "Input phone number: ";
		std::cin >> phoneNumber;

		Driver driver(username, password, firstName, lastName, carNumber, phoneNumber);

		app->registerDriver(std::move(driver));
	}
	catch (std::runtime_error& err)
	{
		std::cout << err.what() << std::endl;
	}
}
