#include "src/cpp/service_implementation/em_service/ZEmService.h"

#include <stdio.h>

#include "src/cpp/em/ZEm.h"
#include "src/cpp/utils/Trace.h"

void ZEmService::FilterEnv(google::protobuf::RpcController* controller,
                           const em::FilterInputT* request,
                           em::PointCollectionT* response,
                           google::protobuf::Closure* done) {
  TRACE("FilterEnv in CPP, request: \n [%s]\n",
         request->DebugString().c_str());

  const EmTypeT em_type{static_cast<EmTypeT>(request->type())};
  const auto ems = request->ems();

  EnvCollectionT es{};
  for (const auto& em : ems) {
    PointT pos{em.position().x(), em.position().y()};
    es.emplace_back(pos, static_cast<EmTypeT>(em.type()));
  }
  const auto ret_ems = FilterE(es, em_type);

  for (const auto& ret_em : ret_ems) {
    auto new_ret_points = response->add_ret_points();
    new_ret_points->set_x(ret_em.x);
    new_ret_points->set_y(ret_em.y);
  }
  TRACE("FilterEnv in CPP, response: \n [%s]\n",
         response->DebugString().c_str());
  return;
}