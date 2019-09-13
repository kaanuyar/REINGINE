#pragma once
#include "EventHandler.h"

class IUpdatable
{
public:
	virtual ~IUpdatable() {}
	virtual void update(float deltaTime) = 0;
	virtual EventHandler& getEventHandler() = 0;
};