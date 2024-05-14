#pragma once
#include <array>
#include <cstdint>
#include <string_view>
namespace app::statemachine {
using std::string_view;
enum class State : uint8_t {
  Init,
  Start,
  Sleep,
};

struct Init {
  static void enter(void);
  static void exit(void);
  static void state_op(void);
  const static inline State meta_state{State::Init};
  const static inline string_view meta_str{"Init"};
};
struct Start {
  static void enter(void);
  static void exit(void);
  static void state_op(void);
  const static inline State meta_state{State::Start};
  const static inline string_view meta_str{"Start"};
};
struct Sleep {
  static void enter(void);
  static void exit(void);
  static void state_op(void);
  const static inline State meta_state{State::Sleep};
  const static inline string_view meta_str{"Sleep"};
};

void enter(void);
void run(void);
void exit(void);
}  // namespace app::statemachine