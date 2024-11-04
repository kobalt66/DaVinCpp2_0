#pragma once
#include <DaVinCppTypes.h>

namespace davincpp
{
    class Timer
    {
    public:
        void start();
        void stop();
        void reset();

        [[nodiscard]] msc fetchTimeMsc() const;
        [[nodiscard]] sec fetchTimeSec() const;
        [[nodiscard]] min fetchTimeMin() const;

    private:
        timestamp m_StartTime;
        timestamp m_StopTime;
    };
}
