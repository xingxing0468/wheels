#include "ZEm.h"

namespace detail {
std::vector<PointT> FilterEnv(const EnvCollectionT& es, const EmTypeT& type) {
  std::vector<PointT> ret;

  for (const auto& e : es) {
    if (e.second == type) {
      ret.push_back(e.first);
    }
  }
  return ret;
}
}  // namespace detail