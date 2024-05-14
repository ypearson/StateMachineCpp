#include "Timer.hpp"

namespace app::os {
Time_ms timer{};

extern "C" void isr_timer_increment(void) { timer += 1; }

Timer::Timer(Time_ms delay) { set_async_delay(delay); }

TimerState Timer::async_delay(void) {
  TimerState state{TimerState::TimerNotExpired};
  Time_ms time_elapsed{};
  Time_ms now_time{rtimer};

  if (now_time >= start_time) {
    time_elapsed = now_time - start_time;
  } else {
    time_elapsed = (Time_ms{MAX_VALUE} - start_time) + now_time + 1;
  }

  if (time_elapsed >= delay_ms) {
    state = TimerState::TimerExpired;
    start_time = now_time;
  }

  return state;
}

void Timer::set_async_delay(Time_ms delay) {
  delay_ms = delay;
  start_time = rtimer;
}
}  // namespace app::os
