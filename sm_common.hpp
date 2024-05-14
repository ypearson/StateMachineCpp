#pragma once
#include <cstdint>
#include <string_view>

#include "logging.h"

using std::string_view;

enum class TransitionTo : bool {
  SELF,
  NOT_SELF,
};

template <typename STATE>
TransitionTo stateTransition(STATE &current_state, const STATE &next_state) {
  TransitionTo transition_to{};

  if (next_state == current_state) {
    transition_to = TransitionTo::SELF;
  } else {
    current_state = next_state;
    transition_to = TransitionTo::NOT_SELF;
  }

  return transition_to;
}

void logTransition(string_view str);
