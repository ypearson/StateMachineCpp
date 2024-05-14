#include "sm_common.hpp"

#include <limits>

void logTransition(string_view str) {
  if (str.size() <= std::numeric_limits<int>::max()) {
    LOGN("{\"state\": \"%.*s\"}", static_cast<int>(str.size()), str.data());
  }
}

void logTransition(string_view str, uint32_t time) {
  if (str.size() <= std::numeric_limits<int>::max()) {
    LOGN("{time: %d, \"state\": \"%.*s\"}", static_cast<int>(str.size()),
         str.data());
  }
}