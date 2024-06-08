from abc import ABCMeta, abstractmethod


class IServiceProbe(metaclass=ABCMeta):
    @abstractmethod
    def SendServiceRequest(self, data):
        pass

    @abstractmethod
    def WaitServiceResponse(self, timeout=2):
        pass

    @abstractmethod
    def RecvServiceResponse(self):
        pass

    @abstractmethod
    def FlushRecvBuff(self):
        pass
