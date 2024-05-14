#pragma once
#include <cstdint>

#include "hal.h"
#include "main.h"

namespace app::gpio {
class GpioBase {
 public:
  GpioBase(GPIO_TypeDef *port, uint16_t pin);
  GPIO_TypeDef *getPort(void) const;
  uint16_t getPinNumber(void) const;

 protected:
  GPIO_TypeDef *port{nullptr};
  uint16_t pin{};
};

class GpioInput : public GpioBase {
 public:
  GpioInput(GPIO_TypeDef *port, uint16_t pin);
  bool read(void) const;
};

class GpioOutput : public GpioBase {
 public:
  GpioOutput(GPIO_TypeDef *port, uint16_t pin);
  bool setHigh(void);
  bool setLow(void);
  void toggle(void);
  GpioOutput &operator=(const bool &rhs);

 private:
  static const inline uint8_t PIN_SET_OFFSET{0U};
  static const inline uint8_t PIN_RESET_OFFSET{16U};
};
}  // namespace app::gpio