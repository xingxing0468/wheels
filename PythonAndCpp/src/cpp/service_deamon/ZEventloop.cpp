// CopyRight of ZED, All Rights Reserved

#include "src/cpp/service_deamon/ZEventloop.h"

#include "assert.h"
#include "src/cpp/utils/Trace.h"
#include "sys/epoll.h"
#include "unistd.h"

namespace {
const int MAX_EVENTS = 10;
}

ZEventloop::ZEventloop() : EpollFd(epoll_create1(EPOLL_CLOEXEC)) {}

void ZEventloop::Run() {
  struct epoll_event events[MAX_EVENTS];
  while (1) {
    TRACE("Waiting for event...");
    int res = epoll_wait(EpollFd, events, MAX_EVENTS, -1);
    if (res < 0) {
      TRACE("Wait event failed, res: [%d]", res);
      continue;
    }
    TRACE("Executing events, count: [%d]", res);
    for (int i = 0; i < res; i++) {
      // ATTENTION: these to static_cast fromm void* always success,
      // and has to been ensure OK by develops when add to EpollFd
      // otherwise crash or unexpectly result occurs, hard to debug
      auto eventData = static_cast<ZEventloop::ZEventData*>(events[i].data.ptr);
      auto eventIter = Events.find(eventData->Fd);
      assert(eventIter != Events.end());  // event must be in Events
      TRACE("Executing event, index: [%d], fd: [%d]", i, eventData->Fd);
      auto handler = static_cast<IEventHandler*>(eventData->Handler);

      if (!handler) {  // actually this static_cast would NOT return NULL, due
                       // to cast form void*
        TRACE("Invalid handler!");
        continue;
      }
      handler->HandleEvent(eventData->Fd);
    }
  }
  return;
}

void ZEventloop::AddFd(int fd, IEventHandler* handler) {
  TRACE("Current event count: [%zu], max: [%d]", Events.size(), MAX_EVENTS);

  if (Events.find(fd) != Events.end()) {
    TRACE("Event with fd: [%d] already exists, abort to add", fd);
    return;
  }
  ZEventloop::ZEventData eventData;
  eventData.Fd = fd;
  eventData.Handler = handler;
  Events.emplace(fd, eventData);
  epoll_event event = {EPOLLIN, {&Events[fd]}};
  int ret = epoll_ctl(EpollFd, EPOLL_CTL_ADD, fd, &event);
  if (ret != 0) {
    TRACE("Add fd to epoll event failed! ret: [%d], fd: [%d]", ret, fd);
  }
  TRACE("Add fd [%d] to epoll event in Epoll fd: [%d], success", fd, EpollFd);
  return;
}

void ZEventloop::RemoveFd(int fd) {
  auto eventIter = Events.find(fd);
  if (eventIter == Events.end()) {
    TRACE("Fd [%d] does NOT exist, abort to remove", fd);
    return;
  }

  if (epoll_ctl(EpollFd, EPOLL_CTL_DEL, fd, nullptr) != 0) {
    TRACE("Fd [%d] remove failed", fd);
    return;
  }

  Events.erase(eventIter);
  TRACE(
      "Remove fd [%d] to epoll event in Epoll fd: [%d], success, current event "
      "count: [%zu]",
      fd, EpollFd, Events.size());
  return;
}
