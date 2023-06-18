#pragma once
#include "Command.h"

class CheckOrderCommand : Command
{
public:
	CheckOrderCommand() = default;

	CheckOrderCommand(const CheckOrderCommand&) = delete;
	CheckOrderCommand& operator=(const CheckOrderCommand&) = delete;

	void execute(Application* app) override;
};
