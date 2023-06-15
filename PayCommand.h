#pragma once
#include "Command.h"

class PayCommand : Command
{
public:
	PayCommand() = default;

	PayCommand(const PayCommand&) = delete;
	PayCommand& operator=(const PayCommand&) = delete;

	void execute(Application* app) override;
};
