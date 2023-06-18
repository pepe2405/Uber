#include "ChangeAddressCommand.h"

void ChangeAddressCommand::execute(Application* app)
{
	MyString addressName;
	int adrX = 0;
	int adrY = 0;

	std::cout << "Input address name: " << std::endl;
	std::cin >> addressName;
	std::cout << "Input address coordinates: " << std::endl;
	std::cin >> adrX;
	std::cin >> adrY;
	std::cout << "Input address description: " << std::endl;
	char buffer[256]{};
	std::cin.getline(buffer, 256);
	std::cin.ignore();
	const MyString adrDescr{ buffer };

	Address address{ addressName, adrX, adrY, adrDescr };

	Driver* driver = dynamic_cast<Driver*>(app->getLoggedUser());
	driver->setAddress(std::move(address));
}
