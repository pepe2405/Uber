#pragma once
#include "Command.h"

class RegDriverCommand : Command
{
public:
	RegDriverCommand() = default;

	RegDriverCommand(const RegDriverCommand&) = delete;
	RegDriverCommand& operator=(const RegDriverCommand&) = delete;

	void execute(Application* app) override;
};
