#pragma once

namespace app::build_info {
struct BuildDetails {
  const char *project_name;
  const char *timestamp;
  const char *firmware_version;
  const char *git_sha;
  const char *git_branch;
  const bool git_is_dirty;
};

const BuildDetails &get_build_information(void);
void print_build_info(void);
}  // namespace app::build_info