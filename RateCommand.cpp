#include "RateCommand.h"

void RateCommand::execute(Application* app)
{
	MyString username;
	try
	{
		std::cout << "Input driver username: " << std::endl;
		std::cin >> username;
		const int driversCount = app->getDrivers().getSize();
		bool containsDriver = false;

		for (int i = 0; i < driversCount; i++)
		{
			if (app->getDrivers()[i].getUsername() == username)
			{
				containsDriver = true;
			}
		}
		if (!containsDriver)
		{
			throw std::runtime_error("Driver doesn't exist.");
		}
	}
	catch (std::runtime_error& rex)
	{
		std::cout << rex.what() << std::endl;
	}

	int rating = 0;
	std::cout << "Input rating: ";
	std::cin >> rating;
	if (rating < 1)
		rating = 1;
	else if (rating > 5)
		rating = 5;

	try
	{
		app->rateDriver(username, rating);
	}
	catch (std::runtime_error& err)
	{
		std::cout << err.what() << std::endl;
	}
}
