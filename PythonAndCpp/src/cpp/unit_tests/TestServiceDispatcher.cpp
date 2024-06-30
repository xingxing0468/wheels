#include <cstdint>
#include <vector>

#include "gtest/gtest.h"
#include "src/cpp/utils/ZServiceDispatcher.h"

namespace {
class TestServiceDispatcher : public testing::Test {
 protected:
  std::vector<uint8_t> request_package_data_{
      'Z',  'e',  'd',  0x20, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
      'S',  'c',  'r',  'u',  'm',  0x00, 0x00, 0x00, 0x00, 0x08, 0x65,
      0x15, 0xe9, 0x03, 0x00, 0x00, 0x1a, 0x03, 'Z',  'e',  'd'};

  std::vector<uint8_t> response_package_data_{
      'Z', 'e', 'd', 0x1a, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 'S', 'c',
      'r', 'u', 'm', 0x00, 0x00, 0x00, 0x00, 0x0a, 0x04, 'Z',  'e',  't', 't'};
};

TEST_F(TestServiceDispatcher, Dispatch) {
  EXPECT_EQ(ZServiceDispatcher::Dispatch(request_package_data_),
            response_package_data_);
};

}  // namespace