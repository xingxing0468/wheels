from google.protobuf import service
from google.protobuf import message
from google.protobuf import descriptor
from google.protobuf import empty_pb2
from z_service_package_helper import ZServicePackageHelper

# TODO UT


class ZServiceChannel(service.RpcChannel):
    def __init__(self, service_probe):
        self._service_probe = service_probe

    def CallMethod(
            self,
            method_descriptor,
            rpc_controller,
            request,
            response_class,
            done):

        service_descriptor = method_descriptor.containing_service
        service_name = service_descriptor.name
        method_index = method_descriptor.index
        serialized_request = request.SerializeToString()

        b_is_oneway_call = (method_descriptor.output_type ==
                            empty_pb2.DESCRIPTOR)
        if b_is_oneway_call == False:
            self._service_probe.FlushRecvBuff()

        self._service_probe.SendServiceRequest(ZServicePackageHelper.Package(
            service_name, method_index, serialized_request))

        if b_is_oneway_call:
            return None

        response_data = self._service_probe.RecvServiceResponse()
        serialized_response_message = (
            ZServicePackageHelper.UnPackage(response_data))[2]
            
        # TODO: reponse service name and method_id sanity check
        response = response_class()
        response.ParseFromString(serialized_response_message)
        return response
