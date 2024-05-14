#pragma once
#include <string_view>

namespace app::build_info {
using std::string_view;
struct BuildDetails {
  string_view timestamp;
  string_view firmware_version;
  string_view git_sha;
  string_view git_branch;
  const bool git_is_dirty;
};

const BuildDetails &get_build_information(void);
void print_build_info(void);
}  // namespace app::build_info