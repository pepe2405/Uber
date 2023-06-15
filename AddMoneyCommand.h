#pragma once
#include "Command.h"

class AddMoneyCommand : Command
{
	AddMoneyCommand() = default;

	AddMoneyCommand(const AddMoneyCommand&) = delete;
	AddMoneyCommand& operator=(const AddMoneyCommand&) = delete;

	void execute(Application* app) override;
};
