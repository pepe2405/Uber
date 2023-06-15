#pragma once
#include "Command.h"

class DeclineOrderCommand : Command
{
public:
	DeclineOrderCommand() = default;

	DeclineOrderCommand(const DeclineOrderCommand&) = delete;
	DeclineOrderCommand& operator=(const DeclineOrderCommand&) = delete;

	void execute(Application* app) override;
};
