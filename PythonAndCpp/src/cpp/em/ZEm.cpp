#include "ZEm.h"

std::vector<PointT> FilterE(const EnvCollectionT& es, const EmTypeT& type) {
  std::vector<PointT> ret;

  for (const auto& e : es) {
    if (std::get<EmTypeT>(e) == type) {
      ret.push_back(std::get<PointT>(e));
    }
  }
  return ret;

}  // namespace