
#include "ZScrumService.h"

#include <stdio.h>

// clang-format off
void ZScrumService::QueryTeam(
  google::protobuf::RpcController* /*controller*/,
  const scrum::Developer* request,
  scrum::ScrumTeam* response,
  google::protobuf::Closure* /*done*/)
{
  printf("QueryTeam in CPP, request: \n [%s]\n", request->DebugString().c_str());
  response->set_name(team_name_);
  team_name_ = "Bingo";
  return;
}