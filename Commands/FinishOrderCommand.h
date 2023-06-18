#pragma once
#include "Command.h"

class FinishOrderCommand : Command
{
public:
	FinishOrderCommand() = default;

	FinishOrderCommand(const FinishOrderCommand&) = delete;
	FinishOrderCommand& operator=(const FinishOrderCommand&) = delete;

	void execute(Application* app) override;
};
