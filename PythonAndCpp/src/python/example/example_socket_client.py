#!/usr/bin/python3

from src.python.service_channel.ipc_service_channel import g_ipc_service_channel

from src.interface.IScrumService_pb2 import Developer
from src.interface.IScrumService_pb2 import Scrum_Stub

from src.interface.IEmService_pb2 import PointT, EmType, EmT, FilterInputT
from src.interface.IEmService_pb2 import Em_Stub

if __name__ == "__main__":
    dev = Developer()
    dev.name = 'zed'
    dev.value = 1001
    dev.id = 101
    scrum_service = Scrum_Stub(g_ipc_service_channel)
    team = scrum_service.QueryTeam(None, dev, None)
    print(team)

    ps = [EmT(position=PointT(x=0, y=0), type=EmType.EMTYPE_UNKNOWN),
          EmT(position=PointT(x=11.1, y=12.2), type=EmType.EMTYPE_CAR),
          EmT(position=PointT(x=21.1, y=22.2), type=EmType.EMTYPE_BUILDING),
          EmT(position=PointT(x=31.1, y=32.2), type=EmType.EMTYPE_CAR)]

    em_service = Em_Stub(g_ipc_service_channel)
    target_em = em_service.FilterEnv(None, FilterInputT(ems=ps, type=EmType.EMTYPE_CAR), None)
    print("Filter result: {}".format(target_em))
