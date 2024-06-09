#include "EventHandler.h"
#include <DaVinCppExceptions.h>
#include <Console.h>

namespace davincpp
{
	std::vector<Event> EventHandler::m_Events;

	void EventHandler::addEvent(Event&& event)
	{
		m_Events.emplace_back(event);
	}

	void EventHandler::onUpdate()
	{
		std::vector<int> expiredEvents;

		timestamp currentTime = clock::now();

		for (int i = 0; i < m_Events.size(); i++) {
			Event& event = m_Events.at(i);
			if (!event.checkTrigger(currentTime)) {
				continue;
			}

			try {
				event.trigger();
				event.reset();
			}
			catch (std::exception& exception) {
				Console::err(exception.what());
				throw event_error();
			}

			if (event.isContinuous()) {
				continue;
			}
			
			expiredEvents.emplace_back(i);
		}

		for (int idx : expiredEvents) {
			m_Events.erase(m_Events.begin() + idx);
		}
	}
}
