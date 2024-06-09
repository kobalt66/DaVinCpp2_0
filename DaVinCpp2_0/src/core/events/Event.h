#pragma once

#include <chrono>
#include <functional>

namespace davincpp
{
	typedef std::chrono::system_clock		clock;
	typedef std::chrono::time_point<clock>	timestamp;
	typedef std::chrono::milliseconds		msc;
	typedef std::chrono::seconds			sec;
	typedef std::chrono::minutes			min;

	class Event
	{
	public:
		Event(std::function<void()> event, msc duration, bool continuous = false);

		bool checkTrigger(timestamp currentTime);
		void trigger();
		void reset();

		bool isContinuous();

	private:
		bool m_Continuous;
		timestamp m_TriggerTime;
		msc m_Duration;
		std::function<void()> m_Event;
	};
}
