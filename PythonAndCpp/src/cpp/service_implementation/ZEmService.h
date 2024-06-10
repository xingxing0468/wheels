#ifndef _Z_EM_SERVICE_H_
#define _Z_EM_SERVICE_H_

#include "IEmService.pb.h"

class ZEmService : public em::Em {
 public:
  // IEmService
  void FilterEnv(google::protobuf::RpcController* controller,
                 const em::FilterInputT* request,
                 em::PointCollectionT* response,
                 google::protobuf::Closure* done) override;
};

#endif