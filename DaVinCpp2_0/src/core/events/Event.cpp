#include "Event.h"

namespace davincpp
{
	Event::Event(std::function<void()> event, msc duration, bool continuous)
		: m_Event(event), m_Duration(duration), m_Continuous(continuous)
	{ 
		reset();
	}


	bool Event::checkTrigger(timestamp currentTime)
	{
		return currentTime >= m_TriggerTime;
	}

	void Event::trigger()
	{
		m_Event();
	}

	void Event::reset()
	{
		m_TriggerTime = clock::now() + m_Duration;
	}


	bool Event::isContinuous()
	{
		return m_Continuous;
	}
}
