from google.protobuf import service
from google.protobuf import empty_pb2
from ..package_helper.z_service_package_helper import (
    ZServicePackageHelper,
    PACKAGE_SIZE_FIELD_BYTES,
)
import time

# TODO UT

TIME_OUT = 2  # seconds


class ZServiceChannel(service.RpcChannel):
    def __init__(self, z_c_extension_service_probe):
        self._service_probe = z_c_extension_service_probe

    def CallMethod(
        self, method_descriptor, rpc_controller, request, response_class, done
    ):

        service_descriptor = method_descriptor.containing_service
        service_name = service_descriptor.name
        method_index = method_descriptor.index
        serialized_request = request.SerializeToString()

        b_is_oneway_call = method_descriptor.output_type == empty_pb2.DESCRIPTOR
        if b_is_oneway_call == False:
            self._service_probe.FlushRecvBuff()

        self._service_probe.SendServiceRequest(
            ZServicePackageHelper.Package(
                service_name, method_index, serialized_request
            )
        )

        if b_is_oneway_call:
            return None

        # First get the head of whole package
        response_data = self._service_probe.RecvServiceResponse()
        if (
            len(response_data)
            < len(ZServicePackageHelper._signature_) + PACKAGE_SIZE_FIELD_BYTES
        ):
            print("ERROR: NO enough data received to get the package head")
        package_size = ZServicePackageHelper.UnPackageHeader(response_data)
        if package_size is None:
            print("ERROR: Invalid package size")
            return None

        # Keep receiving if the package size is larger than the received data
        start_time = time.time()
        while len(response_data) < package_size:
            if time.time() - start_time > TIME_OUT:
                print("ERROR: Timeout while receiving response data")
                return None
            response_data += self._service_probe.RecvServiceResponse()
            # Add timeout here

        payload_offset = (
            len(ZServicePackageHelper._signature_) + PACKAGE_SIZE_FIELD_BYTES
        )
        _, _, serialized_response_message = ZServicePackageHelper.UnPackagePayload(
            response_data[payload_offset:]
        )
        print(
            f"whole received data len: [{len(response_data)}], package size: [{package_size}], serialized response message len: [{len(serialized_response_message)}]"
        )

        # TODO: reponse service name and method_id sanity check
        response = response_class()
        response.ParseFromString(serialized_response_message)
        return response
