#include "Led.hpp"

namespace app::led {
Led::Led(GpioOutput &gpio, Time_ms period)
    : gpio{gpio}, flash_period{period}, timer{period} {}

void Led::flash(void) {
  if (timer.async_delay() == app::os::TimerState::TimerExpired) {
    gpio.toggle();
  }
}
void Led::set_flash_period(Time_ms period) { timer.set_async_delay(period); }
void Led::on(void) { gpio.setHigh(); }
void Led::off(void) { gpio.setLow(); }
void Led::toggle(void) { gpio.toggle(); }
}  // namespace app::led