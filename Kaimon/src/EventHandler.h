#pragma once
#include <vector>
#include <memory>
#include "Event.h"

class EventHandler
{
public:
	void addEventToList(Event aEvent);
	void removeEventFromList(Event aEvent);
	void deleteDeadEventsFromList();
	std::vector<Event>& getEventList();

private:
	std::vector<Event> m_eventList;
};