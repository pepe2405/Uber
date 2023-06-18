#pragma once
#include "Command.h"

class HandleDriverCommand : Command
{
public:
	HandleDriverCommand() = default;

	HandleDriverCommand(const HandleDriverCommand&) = delete;
	HandleDriverCommand& operator=(const HandleDriverCommand&) = delete;

	void execute(Application* app) override;
};
