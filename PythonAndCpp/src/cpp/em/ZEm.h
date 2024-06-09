#ifndef _Z_EM_H_
#define _Z_EM_H_

#include <cstdint>
#include <unordered_map>
#include <vector>

constexpr float kMinX{-100.};
constexpr float kMaxX{100.};
constexpr float kMinY{-100.};
constexpr float kMaxY{100.};
constexpr std::uint32_t kScaleFactor{1000U};  // resolution support to 0.001

struct PointT {
  PointT(const float input_x, const float input_y) : x(input_x), y(input_y){};
  float x{-101.F};
  float y{-101.F};
  bool IsValid() {
    return (x > kMinX) && (x < kMaxX) && (y > kMinY) && (y < kMaxY);
  }
};

bool operator<(const PointT& a, const PointT& b) {
  return (a.y - b.y) * kScaleFactor < -1.F ||
         ((a.y - b.y) * kScaleFactor);  // TODO
}

// TODO
bool operator==(const PointT& a, const PointT& b) {
  return true;  // TODO
}

struct PointTHash {
  std::size_t operator()(const PointT& point) const {
    return ((point.x - kMinX) + (point.y - kMinY) * (kMaxX - kMinX)) *
           kScaleFactor;
  };
};

enum class EmTypeT : std::uint8_t {
  UNKNOWN = 0U,
  Car = 1U,
  Road = 2U,
  Curb = 3U,
  Building = 4U,
  SIZE = 5U,
};

using EnvCollectionT = std::unordered_map<PointT, EmTypeT, PointTHash>;

std::vector<PointT> FilterE(const EnvCollectionT& es, const EmTypeT& type);

#endif