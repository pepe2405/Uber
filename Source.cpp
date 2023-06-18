#include "Application.h"
#include "RunCommand.h"

int main()
{
	Application* uberApplication = &Application::getInstance();
	RunCommand rc;

	while (true)
	{
		rc.execute(uberApplication);
	}
}
