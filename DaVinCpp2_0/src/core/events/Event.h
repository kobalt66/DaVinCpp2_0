#pragma once
#include <DaVinCppTypes.h>
#include <functional>

namespace davincpp
{
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
