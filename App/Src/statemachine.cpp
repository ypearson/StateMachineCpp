
#include "statemachine.hpp"

#include "Timer.hpp"
#include "sm_common.hpp"

namespace app::statemachine {

namespace {
app::os::Timer sm_timer{};
State state{State::Init};
State prevState{State::Init};
} // namespace

void enter(void) {
  // subsystem::OBJECTS.updateState();
}

void run(void) {
  switch (state) {
  case State::Init:
    return Init::state_op();
  case State::Start:
    return Start::state_op();
  case State::Sleep:
    return Sleep::state_op();
  default:
    LOGN("Undefined state error.");
    state = State::Init;
    break;
  }
}

void exit(void) {}

void Init::enter(void) {
  stateTransition(state, meta_state);
  logTransition(meta_str, 0, 0);
}

void Init::state_op(void) {
  if (CONDITION) {
    Init::exit();
    return Start::enter();
  }
}
void Init::exit(void) {}

void Start::enter(void) {
  stateTransition(state, meta_state);
  logTransition(meta_str);
  // ONE TIME ACTIONS
}

void Start::state_op(void) {
  if (CONDITION)
    Start::exit();
  return Sleep::enter();
}
void Start::exit(void) {}

void Sleep::enter(void) {
  stateTransition(state, meta_state);
  logTransition(meta_str);
}

void Sleep::state_op(void) {}
void Sleep::exit(void) {}

} // namespace app::statemachine
