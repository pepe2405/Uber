#pragma once
#include "Command.h"

class RateCommand : Command
{
public:
	RateCommand() = default;

	RateCommand(const RateCommand&) = delete;
	RateCommand& operator=(const RateCommand&) = delete;

	void execute(Application* app) override;
};
