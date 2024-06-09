#pragma once
#include "Event.h"

namespace davincpp
{
	class EventHandler
	{
	public:
		static void addEvent(Event&& event);
		static void onUpdate();

	private:
		static std::vector<Event> m_Events;
	};
}
