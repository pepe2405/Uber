#include "RegClientCommand.h"

void RegClientCommand::execute(Application* app)
{
	try
	{
		MyString username, password, firstName, lastName;
		std::cout << "Input username: ";
		std::cin >> username;
		std::cout << "Input password: ";
		std::cin >> password;
		std::cout << "Input first name: ";
		std::cin >> firstName;
		std::cout << "Input last name: ";
		std::cin >> lastName;

		Client client(std::move(username), std::move(password), std::move(firstName), std::move(lastName));

		app->registerClient(std::move(client));
	}
	catch (std::runtime_error& err)
	{
		std::cout << err.what() << std::endl;
	}
}
