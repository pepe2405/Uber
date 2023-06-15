#include "RegDriverCommand.h"

void RegDriverCommand::execute(Application* app)
{
	try
	{
		MyString username, password, firstName, lastName, carNumber, phoneNumber;
		std::cout << "\nInput username: ";
		std::cin >> username;
		std::cout << "\nInput password: ";
		std::cin >> password;
		std::cout << "\nInput first name: ";
		std::cin >> firstName;
		std::cout << "\nInput last name: ";
		std::cin >> lastName;
		std::cout << "\nInput car number: ";
		std::cin >> carNumber;
		std::cout << "\nInput phone number: ";
		std::cin >> phoneNumber;

		Driver driver(username, password, firstName, lastName, carNumber, phoneNumber);

		app->registerDriver(std::move(driver));
	}
	catch (std::runtime_error& err)
	{
		std::cout << err.what() << std::endl;
	}
}
