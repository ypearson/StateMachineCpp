#include "logging_cfg.h"
#include "hal.h"
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define BUFFER_SIZE 512
static char buffer[BUFFER_SIZE];

void hal_putstring_block(uint8_t *buffer, size_t size) {
  extern UART_HandleTypeDef huart2;
  HAL_UART_Transmit(&huart2, buffer, size, HAL_MAX_DELAY);
}

void nprintf(char const *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  int len = npf_vsnprintf(buffer, BUFFER_SIZE, fmt, args);
  va_end(args);
  if (len > 0) {
    len = MIN(len, BUFFER_SIZE - 1);
    hal_putstring_block((uint8_t*)buffer, len);
  }
}

int logging_vsnprintf(char *buffer, size_t bufsz, char const *format, va_list vlist) {
  return npf_vsnprintf(buffer, bufsz, format, vlist);
}