#include "build_information.hpp"
#include "logging.h"
#include <array>

namespace app::build_info {
const BuildDetails build_details = {
    "2024-01-16T18:43:39Z", "1.0.0", "91b808b65ad4e950db9dfd339d0f76545f692aff",
    "main", true,
};

const BuildDetails &get_build_information(void) { return build_details; }
static std::array<char,256> arr{};

void print_build_info(void) {
  LOGN("------------------------Build Info------------------------");
  LOGN("Firmware version %s %s", build_details.firmware_version.data(),
      build_details.git_is_dirty ? "*Dirty build*" : "*Clean build*");
  LOGN("Build date/time  %s", build_details.timestamp.data());
  LOGN("GIT branch       %s", build_details.git_branch.data());
  LOGN("GIT SHA          %s", build_details.git_sha.data());
  LOGN("------------------------Build Info------------------------");
}
}  // namespace app::build_info
