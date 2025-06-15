from src.python.package_helper.z_service_package_helper import ZServicePackageHelper

import unittest


class TestPackageHelper(unittest.TestCase):

    def test_package(self):
        serialized_data = b"\x08e\x15\xe9\x03\x00\x00\x1a\x03Zed"
        service_name = "Scrum"
        method_id = 2
        packaged_data = ZServicePackageHelper.Package(
            service_name, method_id, serialized_data
        )
        self.assertEqual(
            packaged_data,
            b"Zed\x20\x00\x00\x00\x05\x00\x00\x00Scrum\x02\x00\x00\x00\x08e\x15\xe9\x03\x00\x00\x1a\x03Zed",
        )

    def test_unpackage(self):
        package_data = b"Zed\x20\x00\x00\x00\x05\x00\x00\x00Scrum\x02\x00\x00\x00\x08e\x15\xe9\x03\x00\x00\x1a\x03Zed"
        [service_name, method_id, serialized_data] = ZServicePackageHelper.UnPackage(
            package_data
        )
        self.assertEqual(service_name, "Scrum")
        self.assertEqual(method_id, 0x02)
        self.assertEqual(serialized_data, b"\x08e\x15\xe9\x03\x00\x00\x1a\x03Zed")

    def test_unpackage_header(self):
        package_data = b"Zed\x20\x00\x00\x00\x05\x00\x00\x00Scrum\x02\x00\x00\x00\x08e\x15\xe9\x03\x00\x00\x1a\x03Zed"
        package_size = ZServicePackageHelper.UnPackageHeader(package_data)
        self.assertEqual(package_size, 32)

    def test_unpackage_payload(self):
        package_data = b"Zed\x20\x00\x00\x00\x05\x00\x00\x00Scrum\x02\x00\x00\x00\x08e\x15\xe9\x03\x00\x00\x1a\x03Zed"
        [service_name, method_id, serialized_data] = (
            ZServicePackageHelper.UnPackagePayload(package_data[7:])
        )
        self.assertEqual(service_name, "Scrum")
        self.assertEqual(method_id, 0x02)
        self.assertEqual(serialized_data, b"\x08e\x15\xe9\x03\x00\x00\x1a\x03Zed")


if __name__ == "__main__":
    unittest.main()
