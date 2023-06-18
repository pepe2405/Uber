#pragma once
#include "Command.h"

class RegClientCommand : Command
{
public:
	RegClientCommand() = default;

	RegClientCommand(const RegClientCommand&) = delete;
	RegClientCommand& operator=(const RegClientCommand&) = delete;

	void execute(Application* app) override;
};
