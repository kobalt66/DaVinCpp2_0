#include "Timer.h"

namespace davincpp
{
    void Timer::start()
    {
        m_StartTime = clock::now();
    }

    void Timer::stop()
    {
        m_StopTime = clock::now();
    }

    void Timer::reset()
    {
        m_StartTime = timestamp();
        m_StopTime = timestamp();
    }


    msc Timer::fetchTimeMsc() const
    {
        return std::chrono::duration_cast<msc>(m_StopTime - m_StartTime);
    }

    sec Timer::fetchTimeSec() const
    {
        return std::chrono::duration_cast<sec>(m_StopTime - m_StartTime);
    }

    min Timer::fetchTimeMin() const
    {
        return std::chrono::duration_cast<min>(m_StopTime - m_StartTime);
    }
}
