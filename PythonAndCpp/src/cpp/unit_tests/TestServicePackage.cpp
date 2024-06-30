#include <cstdint>
#include <vector>

#include "gtest/gtest.h"
#include "src/cpp/utils/ZServicePackage.h"

namespace {

class TestServicePackage : public testing::Test {
 protected:
  std::vector<uint8_t> serialized_data_{0x08, 'e',  0x15, 0xe9, 0x03, 0x00,
                                        0x00, 0x1a, 0x03, 'Z',  'e',  'd'};
  std::vector<uint8_t> packaged_data_{
      'Z',  'e',  'd',  0x20, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
      'S',  'c',  'r',  'u',  'm',  0x02, 0x00, 0x00, 0x00, 0x08, 0x65,
      0x15, 0xe9, 0x03, 0x00, 0x00, 0x1a, 0x03, 'Z',  'e',  'd'};
  std::string service_name_{"Scrum"};
  int method_index_{2};
};

TEST_F(TestServicePackage, Pack) {
  EXPECT_EQ(
      ZServicePackage::Pack(service_name_, method_index_, serialized_data_),
      packaged_data_);
};

TEST_F(TestServicePackage, Unpack) {
  std::string actual_service_name{""};
  uint32_t actual_method_index{0xFFFFFFFF};

  EXPECT_EQ(ZServicePackage::Unpack(packaged_data_, actual_service_name,
                                    actual_method_index),
            serialized_data_);
  EXPECT_EQ(actual_service_name, service_name_);
  EXPECT_EQ(actual_method_index, method_index_);
};

}  // namespace
