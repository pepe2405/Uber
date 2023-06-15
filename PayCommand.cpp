#include "PayCommand.h"

void PayCommand::execute(Application* app)
{
	int ordId = 0;
	std::cout << "Input order ID: ";
	std::cin >> ordId;
	double amount = 0;
	std::cout << "Input amount: ";
	std::cin >> amount;

	try
	{
		app->pay(ordId, amount);
	}
	catch (std::runtime_error& err)
	{
		std::cout << err.what() << std::endl;
	}
}
