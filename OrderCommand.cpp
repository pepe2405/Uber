#include "OrderCommand.h"
#include <iostream>


void OrderCommand::execute(Application*  app)
{
	MyString orginName;
	int orX = 0;
	int orY = 0;

	std::cout << "Input address name: ";
	std::cin >> orginName;
	std::cout << "Input address coordinates: ";
	std::cin >> orX;
	std::cin >> orY;
	std::cout << "Input address description: ";
	char bufferOr[256]{};
	std::cin.getline(bufferOr, 256);
	std::cin.ignore();
	const MyString descr (bufferOr);

	Address origin(orginName, orX, orY, descr);

	unsigned passengers = 0;
	std::cin >> passengers;

	MyString destinationName;
	int destX = 0;
	int destY = 0;

	std::cout << "Input destination name: ";
	std::cin >> destinationName;
	std::cin >> destX;
	std::cin >> destY;
	std::cout << "Input destination description: ";
	char bufferDest[256]{};
	std::cin.getline(bufferDest, 256);
	std::cin.ignore();
	const MyString destinationDescription(bufferDest);

	Address destination{ destinationName, destX, destY, destinationDescription };

	try
	{
		Order order(dynamic_cast<Client*>(app->getLoggedUser().operator->()), app->getClosestDriver(orX, orY),
		            std::move(origin), std::move(destination), passengers);
		app->addOrder(std::move(order));

	}
	catch (std::runtime_error& err)
	{
		std::cout << err.what() << std::endl;
	}
}

