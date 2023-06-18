#include "RegisterCommand.h"

#include "RegClientCommand.h"
#include "RegDriverCommand.h"

void RegisterCommand::execute(Application* app)
{
	RegDriverCommand rdc;
	RegClientCommand rcc;
	int n = 0;
	std::cout << "Choose:\n 1) Client\n 2) Driver\n";
	std::cin >> n;
	switch (n)
	{
	case 1: rcc.execute(app); break;
	case 2: rdc.execute(app); break;
	default: std::cout << "Unknown command!\n"; break;
	}
}
