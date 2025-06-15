import struct

# Request:
# -------------------------------------------------------------------------------------------------
# | "Zed" | 4 byte length | 4 bytes service name length | service name | method index | input data|
# -------------------------------------------------------------------------------------------------

# Response:
# --------------------------------------------------------------------------------------------------
# | "Zed" | 4 byte length | 4 bytes service name length | service name | method index | output data|
# --------------------------------------------------------------------------------------------------

PACKAGE_SIZE_FIELD_BYTES = 4


class ZServicePackageHelper:
    _signature_ = "Zed"

    @staticmethod
    def Package(service_name, method_index, serialized_data):
        package_size = (
            len(ZServicePackageHelper._signature_)
            + len(service_name)
            + len(serialized_data)
            + 4
            + 4
            + 4
        )  # len(service name) + len(int) + method_index(int)
        if package_size > 0xFFFFFFFF:
            return None
        return b"".join(
            [
                b"Zed",
                struct.pack("<i", package_size),
                struct.pack("<i", len(service_name)),
                bytes(service_name, encoding="utf-8"),
                struct.pack("<i", method_index),
                serialized_data,
            ]
        )

    @staticmethod
    def UnPackage(package_data):
        offset = 0

        # signature
        signature = str(
            package_data[
                offset : (offset + len(ZServicePackageHelper._signature_))
            ].decode("utf-8")
        )
        if signature != ZServicePackageHelper._signature_:
            print(
                "Error: Invalid signature, expected: [{}], actual: [{}]".format(
                    ZServicePackageHelper._signature_, signature
                )
            )
            return None
        offset += offset + len(ZServicePackageHelper._signature_)

        # package_size and service_name_size
        package_size, service_name_size = struct.unpack(
            "<ii", package_data[offset : (offset + 4 + 4)]
        )
        if package_size != len(package_data):
            print(
                "Error: Invalid package size, expected: [{}], actual: [{}]".format(
                    package_size, len(package_data)
                )
            )
            return None
        offset += 8

        # service_name
        service_name = str(
            package_data[offset : (offset + service_name_size)].decode("utf-8")
        )
        offset += service_name_size

        # method_id
        (method_id,) = struct.unpack("<i", package_data[offset : (offset + 4)])
        offset += 4

        return service_name, method_id, package_data[offset:package_size]

    @staticmethod
    def UnPackageHeader(package_data):
        if (
            len(package_data)
            < len(ZServicePackageHelper._signature_) + PACKAGE_SIZE_FIELD_BYTES
        ):  # "Zed" + package_size field length
            print(
                f"ERROR: invalid header package length [{len(package_data)}], expected at least [{len(ZServicePackageHelper._signature_) + PACKAGE_SIZE_FIELD_BYTES}]"
            )
        offset = 0

        # signature
        signature = str(
            package_data[
                offset : (offset + len(ZServicePackageHelper._signature_))
            ].decode("utf-8")
        )
        if signature != ZServicePackageHelper._signature_:
            print(
                "Error: Invalid signature, expected: [{}], actual: [{}]".format(
                    ZServicePackageHelper._signature_, signature
                )
            )
            return None
        offset += offset + len(ZServicePackageHelper._signature_)

        # package_size
        (package_size,) = struct.unpack(
            "<i", package_data[offset : (offset + PACKAGE_SIZE_FIELD_BYTES)]
        )

        return package_size

    @staticmethod
    def UnPackagePayload(payload_data):
        offset = 0
        # service_name_size
        (service_name_size,) = struct.unpack("<i", payload_data[offset : (offset + 4)])

        offset += 4

        # service_name
        service_name = str(
            payload_data[offset : (offset + service_name_size)].decode("utf-8")
        )
        offset += service_name_size

        # method_id
        (method_id,) = struct.unpack("<i", payload_data[offset : (offset + 4)])
        offset += 4

        return service_name, method_id, payload_data[offset:]
