from ..service_client.z_service_channel import ZServiceChannel
from ..service_probe.z_c_extension_service_probe import ZCExtensionServiceProbe

g_local_service_channel = ZServiceChannel(ZCExtensionServiceProbe())