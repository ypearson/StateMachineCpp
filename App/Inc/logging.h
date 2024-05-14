#ifndef LOGGING_H_
#define LOGGING_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LOGGING_ENABLED
#include <stdarg.h>
#include <stddef.h>
void hal_putstring_block(uint8_t *buffer, size_t size);
void nprintf(char const *fmt, ...);
int logging_vsnprintf(char *buffer, size_t bufsz, char const *format,
                      va_list vlist);
#define __NEWLINE__ nprintf("\r\n")
#define __FILENAMEX__                                                       \
  (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 \
                                    : __FILE__)
#define LOG(...) nprintf(__VA_ARGS__);
#define LOGN(...)       \
  nprintf(__VA_ARGS__); \
  __NEWLINE__
#define LOGV(params, ...)                                                      \
  nprintf("%s:%d " params, __FILENAMEX__, __LINE__ __VA_OPT__(, ) __VA_ARGS__); \
  __NEWLINE__
#else
#define __NEWLINE__ printf("\n")
#define LOG(...)
#define LOGN(...)      \
  printf(__VA_ARGS__); \
  __NEWLINE__
#define LOGV(params, ...)
#endif
#ifdef __cplusplus
}
#endif

#endif
