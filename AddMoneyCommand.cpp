#include "AddMoneyCommand.h"

void AddMoneyCommand::execute(Application* app)
{
	double amount = 0;
	std::cout << "Input amount: ";
	std::cin >> amount;
	if (amount <= 0)
	{
		amount = 1;
	}

	app->getLoggedUser()->addMoney(amount);
}
