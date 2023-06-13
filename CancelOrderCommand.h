#pragma once
#include "Command.h"

class CancelOrderCommand : Command
{
public:
	CancelOrderCommand() = default;

	CancelOrderCommand(const CancelOrderCommand&) = delete;
	CancelOrderCommand& operator=(const CancelOrderCommand&) = delete;

	void execute(Application* app) override;
};
