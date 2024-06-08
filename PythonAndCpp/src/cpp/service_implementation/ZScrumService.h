#ifndef _Z_SCRUM_SERVICE_H_
#define _Z_SCRUM_SERVICE_H_

#include "IScrumService.pb.h"

// clang-format off
class ZScrumService : public scrum::Scrum
{
public:
  // IScrumService
  void QueryTeam(
      google::protobuf::RpcController *controller,
      const scrum::Developer *request,
      scrum::ScrumTeam *response,
      google::protobuf::Closure *done) override;

private:
  std::string team_name_{"Zett"};
};

#endif