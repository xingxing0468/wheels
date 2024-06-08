#!/usr/bin/python3

from IScrumService_pb2 import Developer
from IScrumService_pb2 import Scrum_Stub
from z_service_channel import ZServiceChannel
from service_probe import ZCExtensionServiceProbe


if __name__ == "__main__":
    dev = Developer()
    dev.name = 'zed'
    dev.value = 1001
    dev.id = 101
    scrum_service = Scrum_Stub(ZServiceChannel(ZCExtensionServiceProbe()))
    team = scrum_service.QueryTeam(None, dev, None)
    print(team)
    team = scrum_service.QueryTeam(None, dev, None)
    print(team)
