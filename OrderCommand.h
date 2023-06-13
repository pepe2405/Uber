#pragma once
#include "Command.h"

class OrderCommand : public Command
{
public:
	OrderCommand() = default;

	OrderCommand(const OrderCommand&) = delete;
	OrderCommand& operator=(const OrderCommand&) = delete;

	void execute(Application* app) override;
};
