#include "HandleDriverCommand.h"

#include "AcceptOrderCommand.h"
#include "ChangeAddressCommand.h"
#include "DeclineOrderCommand.h"
#include "FinishOrderCommand.h"

void HandleDriverCommand::execute(Application* app)
{
	ChangeAddressCommand cac;

	AcceptOrderCommand aoc;
	DeclineOrderCommand doc;
	FinishOrderCommand foc;


	int n = 0;
	std::cout << "Choose:\n 1)Change Address\n 2)Check Messages\n 3)Accept Order\n 4)Decline Order\n 5)Finish Order\n 6)Logout\n 7)Exit\n";
	std::cin >> n;

	switch (n)
	{
	case 1: cac.execute(app);  break;
	case 2: app->checkMessages(); break;
	case 3: aoc.execute(app); break;
	case 4: doc.execute(app); break;
	case 5: foc.execute(app); break;
	case 6: app->logout(); break;
	case 7: break;
	default: std::cout << "Unknown command!\n"; break;
	}
}
