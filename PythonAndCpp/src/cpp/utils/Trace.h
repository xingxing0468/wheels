// CopyRight of ZED, All Rights Reserved

#ifndef _TRACE_H_
#define _TRACE_H_

#include "stdio.h"

#define DEBUG_TRACE(fmt, args...) \
  Trace::PrintTime();             \
  printf("%-35s %-20s %4d\t" fmt "\n", __FILE__, __FUNCTION__, __LINE__, ##args)

#define TRACE(fmt, args...) \
  Trace::PrintTime();       \
  printf("\t" fmt "\n", ##args)

namespace Trace {

extern void PrintTime();

}
#endif
