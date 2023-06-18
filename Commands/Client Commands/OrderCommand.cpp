#include "OrderCommand.h"
#include <iostream>


void OrderCommand::execute(Application*  app)
{
	MyString orginName;
	int orX = 0;
	int orY = 0;

	std::cout << "Input address name: ";
	std::cin >> orginName;
	std::cout << "Input address coordinates: \n";
	std::cout << "X: ";
	std::cin >> orX;
	std::cout << "Y: ";
	std::cin >> orY;
	std::cout << "Input address description: ";
	char bufferOr[256]{};
	std::cin.ignore();
	std::cin.getline(bufferOr, 256);
	const MyString descr (bufferOr);

	Address origin(orginName, orX, orY, descr);

	std::cout << "Enter passenger\n";
	unsigned passengers = 0;
	std::cin >> passengers;

	MyString destinationName;
	int destX = 0;
	int destY = 0;

	std::cout << "Input destination name: ";
	std::cin >> destinationName;
	std::cout << "X: ";
	std::cin >> destX;
	std::cout << "Y: ";
	std::cin >> destY;
	std::cout << "Input destination description: ";
	char bufferDest[256]{};
	std::cin.ignore();
	std::cin.getline(bufferDest, 256);
	const MyString destinationDescription(bufferDest);

	Address destination{ destinationName, destX, destY, destinationDescription };

	try
	{
		Order order(dynamic_cast<Client*>(app->getLoggedUser()), app->getClosestDriver(orX, orY), std::move(origin), std::move(destination), passengers);
		app->addOrder(std::move(order));

	}
	catch (std::runtime_error& err)
	{
		std::cout << err.what() << std::endl;
	}
}

