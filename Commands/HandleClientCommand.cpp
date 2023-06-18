#include "HandleClientCommand.h"

#include "AddMoneyCommand.h"
#include "CancelOrderCommand.h"
#include "CheckOrderCommand.h"
#include "OrderCommand.h"
#include "PayCommand.h"
#include "RateCommand.h"

void HandleClientCommand::execute(Application* app)
{
	OrderCommand oc;
	CheckOrderCommand coc;
	CancelOrderCommand cloc;
	PayCommand pc;
	RateCommand rc;
	AddMoneyCommand amc;

	int n = 0;
	std::cout << "Choose:\n 1)Order\n 2)Check Order\n 3)Cancel Order\n 4)Pay\n 5)Rate\n 6)Add Money\n 7) Check Messages\n 8)Logout\n 9)Exit\n";
	std::cin >> n;
	//TODO: fix char or string input

	switch (n)
	{
	case 1: oc.execute(app); break;
	case 2: coc.execute(app); break;
	case 3: cloc.execute(app); break;
	case 4: pc.execute(app); break;
	case 5: rc.execute(app); break;
	case 6: amc.execute(app); break;
	case 7: app->checkMessages(); break;
	case 8: app->logout(); break;
	case 9: break;
	default: std::cout << "Unknown command!\n"; break;
	}
}
