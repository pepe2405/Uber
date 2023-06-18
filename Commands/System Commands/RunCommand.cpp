#include "RunCommand.h"

#include "HandleClientCommand.h"
#include "HandleDriverCommand.h"
#include "HandleNoneCommand.h"


void RunCommand::execute(Application* app)
{
	const LoggedUserType type = app->getType();

	HandleNoneCommand hnc;
	HandleClientCommand hcc;
	HandleDriverCommand hdc;

	switch (type)
	{
	case LoggedUserType::driver: hdc.execute(app);
		break;
	case LoggedUserType::client: hcc.execute(app);
		break;
	case LoggedUserType::none: hnc.execute(app);
		break;
	}
}
