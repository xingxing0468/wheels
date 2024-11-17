from ..service_client.z_service_channel import ZServiceChannel
from ..service_probe.z_socket_service_probe import ZSocketServiceProbe

g_ipc_service_channel = ZServiceChannel(ZSocketServiceProbe())