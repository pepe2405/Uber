#include "CheckOrderCommand.h"

void CheckOrderCommand::execute(Application* app)
{
	try
	{
		int ordId = 0;
		std::cout << "Input order ID: ";
		std::cin >> ordId;

		const DynamicArray<Order>* ordersPtr = &app->getOrders();
		for (size_t i = 0; i < ordersPtr->getSize(); i++)
		{
			if (ordersPtr->operator[](i).getId() == ordId)
			{
				ordersPtr->operator[](i).print();
				return;
			}
		}
		throw std::runtime_error("Order not found\n");
	}
	catch (std::runtime_error& rex)
	{
		std::cout << rex.what() << std::endl;
	}
	
}
