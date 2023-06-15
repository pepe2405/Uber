#pragma once
#include "Command.h"

class AcceptOrderCommand : Command
{
public:
	AcceptOrderCommand() = default;

	AcceptOrderCommand(const AcceptOrderCommand&) = delete;
	AcceptOrderCommand& operator=(const AcceptOrderCommand&) = delete;

	void execute(Application* app) override;
};
