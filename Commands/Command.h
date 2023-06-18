#pragma once
#include <iostream>

#include "Application.h"

class Command
{
public:
	virtual ~Command() = default;
	void virtual execute(Application* app) = 0;
};
