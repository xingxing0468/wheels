// CopyRight of ZED, All Rights Reserved

#include "stdio.h"

#include <time.h>
#include <sys/time.h>

namespace Trace {

void PrintTime()
{
  time_t tt;
  struct timeval tv;
  gettimeofday(&tv, NULL);
  char tmpbuf[80];

  tt=time(NULL);
  strftime(tmpbuf, 80, "%H:%M:%S", localtime(&tt));
  printf("%s:%-3ld ", tmpbuf, tv.tv_usec / 1000);
  return;
}

}
