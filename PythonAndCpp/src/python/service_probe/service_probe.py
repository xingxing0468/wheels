from .i_service_probe import IServiceProbe
from src.python.service_probe.libpy_binding import zprobe

class ZCExtensionServiceProbe(IServiceProbe):
    def __init__(self):
        self._out_data = b''

    def SendServiceRequest(self, data):
        self._out_data = zprobe.communicate(data)
        return len(data)

    def WaitServiceResponse(self, timeout=2):
        return True

    def RecvServiceResponse(self):
        return self._out_data

    def FlushRecvBuff(self):
        self._out_data = ''
    pass
