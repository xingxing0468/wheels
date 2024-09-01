from src.python.package_helper.z_service_package_helper import ZServicePackageHelper

import unittest


class TestPackageHelper(unittest.TestCase):

    def test_package(self):
        serialized_data = b'\x08e\x15\xe9\x03\x00\x00\x1a\x03Zed'
        service_name = 'Scrum'
        method_id = 2
        packaged_data = ZServicePackageHelper.Package(
            service_name, method_id, serialized_data)
        self.assertEqual(
            packaged_data, b'Zed\x20\x00\x00\x00\x05\x00\x00\x00Scrum\x02\x00\x00\x00\x08e\x15\xe9\x03\x00\x00\x1a\x03Zed')

    def test_unpackage(self):
        package_data = b'Zed\x20\x00\x00\x00\x05\x00\x00\x00Scrum\x02\x00\x00\x00\x08e\x15\xe9\x03\x00\x00\x1a\x03Zed'
        [service_name, method_id, serialized_data] = ZServicePackageHelper.UnPackage(
            package_data)
        self.assertEqual(service_name, 'Scrum')
        self.assertEqual(method_id, 0x02)
        self.assertEqual(
            serialized_data, b'\x08e\x15\xe9\x03\x00\x00\x1a\x03Zed')
        pass
