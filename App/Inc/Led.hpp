#pragma once
#include "Gpio.hpp"
#include "Timer.hpp"

namespace app::led {
using namespace app::os;
using namespace app::gpio;

class Led {
 public:
  Led(GpioOutput &gpio, Time_ms period = 100);
  void set_flash_period(Time_ms period);
  void flash(void);
  void on(void);
  void off(void);
  void toggle(void);

 private:
  GpioOutput &gpio;
  Time_ms flash_period;
  Timer timer;
};
}  // namespace app::led