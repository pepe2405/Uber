#pragma once
#include "Command.h"

class ChangeAddressCommand : Command
{
public:
	ChangeAddressCommand() = default;

	ChangeAddressCommand(const ChangeAddressCommand&) = delete;
	ChangeAddressCommand& operator=(const ChangeAddressCommand&) = delete;

	void execute(Application* app) override;
};
