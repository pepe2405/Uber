#include "AcceptOrderCommand.h"

void AcceptOrderCommand::execute(Application* app)
{
	int ordId = 0;
	std::cout << "Input order ID: ";
	std::cin >> ordId;

	try
	{
		const int ordCount = app->getOrders().getSize();
		bool containsOrder = false;
		for (int i = 0; i < ordCount; i++)
		{
			if (app->getOrders()[i].getId() == ordId)
			{
				containsOrder = true;
			}
		}
		containsOrder = false;

		if (!containsOrder)
		{
			throw std::runtime_error("No order with such ID!\n");
		}
		app->acceptOrder(ordId);
		short minutes = 0;
		std::cout << "Input minutes: ";
		std::cin >> minutes;
		app->setMinutes(ordId, minutes);



	}
	catch (std::runtime_error& err)
	{
		std::cout << err.what() << std::endl;
	}
}
