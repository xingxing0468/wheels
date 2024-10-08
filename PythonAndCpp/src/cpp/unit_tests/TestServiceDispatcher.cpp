#include <cstdint>
#include <vector>

#include "gtest/gtest.h"
#include "src/cpp/service_factory/common/ZRuntimeServiceFactoryCollector.h"
#include "src/cpp/service_factory/common/ZStaticServiceFactoryCollector.h"
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

  std::vector<uint8_t> empty_response_package_data_{
      'Z',  'e', 'd', 0x14, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00,
      0x00, 'S', 'c', 'r',  'u',  'm',  0x00, 0x00, 0x00, 0x00};
  ZServiceDispatcher unit_;
};

TEST_F(TestServiceDispatcher, DispatchWithStaticServiceFactory) {
  unit_.ResetServiceFactories<ZStaticServiceFactoryCollector>();
  EXPECT_EQ(unit_.Dispatch(request_package_data_), response_package_data_);
};

TEST_F(TestServiceDispatcher, DispatchWithRuntimeServiceFactory) {
  unit_.ResetServiceFactories<ZRuntimeServiceFactoryCollector>(
      "src/cpp/service_factory/scrum_service_factory");
  EXPECT_EQ(unit_.Dispatch(request_package_data_), response_package_data_);
};

TEST_F(TestServiceDispatcher,
       DispatchWithRuntimeServiceFactory_WithoutSupportedService) {
  unit_.ResetServiceFactories<ZRuntimeServiceFactoryCollector>(".");
  EXPECT_EQ(unit_.Dispatch(request_package_data_),
            empty_response_package_data_);
};

}  // namespace