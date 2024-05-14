#include "Timer.hpp"

namespace {
app::os::Timer hrtbeat_timer{100};
}

int main(void) {

  app::statemachine::Init::enter();
  for (;;) {
    if (hrtbeat_timer.async_delay() == app::os::TimerState::TimerExpired) {
      gpio::hrtbeat_led.toggle();
    }
    app::statemachine::enter();
    app::statemachine::run();
    app::statemachine::exit();
  }

  return 0;
}