from .i_service_probe import IServiceProbe
import socket


class ZSocketServiceProbe(IServiceProbe):
    def __init__(self):
        IPC_ADDRESS = "/tmp/IpcSocket"
        self._socket = socket.socket(family=socket.AF_UNIX, type=socket.SOCK_STREAM)
        self._out_data = b""
        self._socket.connect("/tmp/IpcSocket")

    def SendServiceRequest(self, data):
        return self._socket.send(data)

    def WaitServiceResponse(self, timeout=2):
        return True

    def RecvServiceResponse(self):
        MAX_SIZE_FOR_SEND_RECV = 1 * 1024 * 1024
        self._out_data = self._socket.recv(MAX_SIZE_FOR_SEND_RECV)
        return self._out_data

    def FlushRecvBuff(self):
        self._out_data = b""
