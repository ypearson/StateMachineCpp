#pragma once
#include <cstdint>
#include <limits>

namespace app::os {
using Time_ms = uint32_t;
// using Time_ms = uint64_t;
extern Time_ms timer;

enum class TimerState : bool {
  TimerNotExpired = false,
  TimerExpired = true,
};

class Timer {
 public:
  Timer(Time_ms delay = 1000);
  TimerState async_delay(void);
  void set_async_delay(Time_ms delay);
  void reset(void) { start_time = rtimer; }
  static Time_ms now(void) { return rtimer; }

 private:
  Time_ms delay_ms{};
  Time_ms start_time{};
  static inline const Time_ms &rtimer{timer};
  static inline constexpr uint32_t MAX_VALUE{
      std::numeric_limits<uint32_t>::max()};
};
}  // namespace app::os