#pragma once
#include "Command.h"

class LoginCommand : Command
{
public:
	LoginCommand() = default;

	LoginCommand(const LoginCommand&) = delete;
	LoginCommand& operator=(const LoginCommand&) = delete;

	void execute(Application* app) override;
};
