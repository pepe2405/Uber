#include "CancelOrderCommand.h"

void CancelOrderCommand::execute(Application* app)
{
	try
	{
		int ordId = 0;
		std::cout << "Input order ID: ";
		std::cin >> ordId;

		app->cancelOrder(ordId);
	}
	catch (std::runtime_error& err)
	{
		std::cout << err.what() << std::endl;
	}
}
