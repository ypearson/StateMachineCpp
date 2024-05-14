#include "Gpio.hpp"

namespace app::gpio {
GpioBase::GpioBase(GPIO_TypeDef *port, uint16_t pin) : port{port}, pin{pin} {}

GpioOutput::GpioOutput(GPIO_TypeDef *port, uint16_t pin)
    : GpioBase{port, pin} {}

uint16_t GpioBase::getPinNumber(void) const { return pin; }

GPIO_TypeDef *GpioBase::getPort(void) const { return port; }

GpioInput::GpioInput(GPIO_TypeDef *port, uint16_t pin) : GpioBase{port, pin} {}

bool GpioInput::read(void) const { return (port->IDR & pin) ? true : false; }

bool GpioOutput::setHigh(void) {
  port->BSRR = pin << PIN_SET_OFFSET;
  return true;
}

bool GpioOutput::setLow(void) {
  port->BSRR = pin << PIN_RESET_OFFSET;
  return false;
}

void GpioOutput::toggle(void) {
  const uint32_t odr{port->ODR};
  port->BSRR = ((odr & pin) << PIN_RESET_OFFSET) | (~odr & pin);
}

GpioOutput &GpioOutput::operator=(const bool &rhs) {
  if (rhs == true) {
    setHigh();
  } else {
    setLow();
  }
  return *this;
}
}  // namespace app::gpio