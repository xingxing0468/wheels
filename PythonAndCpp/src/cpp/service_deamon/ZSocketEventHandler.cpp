#include "src/cpp/service_deamon/ZSocketEventHandler.h"

#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "src/cpp/utils/Trace.h"

namespace {
const std::string IPC_SOCKET_NAME = "/tmp/IpcSocket";
}

ZSocketEventHandler::ZSocketEventHandler(ZEventloop& eventloop,
                                         const ZServiceDispatcher& dispatcher)
    : eventloop_{eventloop}, dispatcher_{dispatcher} {
  struct sockaddr_un serverAddr;
  auto init = [&, this]() -> bool {
    if ((this->server_socket_fd_ = socket(PF_LOCAL, SOCK_STREAM, 0)) == -1) {
      return false;
    }
    // Set NON_BLOCKING
    int flags = fcntl(this->server_socket_fd_, F_GETFL);
    if (flags == -1) {
      TRACE("fcntl(F_GETFL) FAILED");
      return false;
    }
    if (fcntl(this->server_socket_fd_, F_SETFL, flags | O_NONBLOCK) == -1) {
      TRACE("fcntl(F_SETFL) failed");
      return false;
    }
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sun_family = AF_LOCAL;
    // Use abstract name space, leave first byte as '\0'
    strcpy(serverAddr.sun_path + 1, this->server_socket_name_.c_str());
    return true;
  };

  auto bindServerSocket = [&, this]() {
    if (bind(this->server_socket_fd_, (struct sockaddr*)(&serverAddr),
             sizeof(serverAddr)) == -1) {
      TRACE("ERROR: Bind failed");
      return false;
    }
    TRACE("Binded in constructor");
    return true;
  };

  auto listenServerSocket = [&, this]() {
    if (listen(this->server_socket_fd_, SOMAXCONN) == -1) {
      TRACE("ERROR: Listen socket fail");
      close(this->server_socket_fd_);
      return false;
    }
    TRACE("Listen constructor");
    return true;
  };

  if (!init()) {
    TRACE("ERROR: Fail to init socket!");
    return;
  }

  if (!bindServerSocket()) {
    TRACE("ERROR: Fail to bind socket!");
    return;
  }
  if (!listenServerSocket()) {
    TRACE("Fail to listen socket!");
  }

  eventloop_.AddFd(server_socket_fd_, std::shared_ptr<IEventHandler>(this));
}

ZSocketEventHandler::~ZSocketEventHandler() {
  close(server_socket_fd_);
  auto closeConnection = [&]() {};

  auto closeServerSocket = [&]() {};

  auto cleanUp = [&]() {};

  closeConnection();
  closeServerSocket();
  cleanUp();
}

void ZSocketEventHandler::HandleEvent(int fd) {
  if (fd == server_socket_fd_) {
    HandleConnect();
  } else if (fd == server_accepted_fd_) {
    HandleCall();
  } else {
    TRACE("Invalid Fd[%d] received, ServerSocketFd: [%d], AcceptedFd: [%d]", fd,
          server_socket_fd_, server_accepted_fd_);
  }
}

void ZSocketEventHandler::HandleConnect() {
  if ((server_accepted_fd_ = accept(server_socket_fd_, NULL, NULL)) == -1) {
    TRACE("ERROR: Accept once failed: [%d]", errno);
    return;
  }

  eventloop_.AddFd(server_accepted_fd_, std::shared_ptr<IEventHandler>(this));
}

void ZSocketEventHandler::HandleCall() {
  std::uint8_t payload[ZServiceDispatcher::MAX_PARAM_SERIALIZED_SIZE + 1] = {
      0U};

  // We never known how long we need to receive
  // Since its a local socket and only buffer copy from kernel to userspace
  // with limited payload length, should be OK
  const auto length = ReceiveAllFromSocket(server_accepted_fd_, payload, 0);
  if (length < 0) {
    eventloop_.RemoveFd(server_socket_fd_);
    close(server_socket_fd_);
  } else {
    std::vector<std::uint8_t> ipc_message;
    ipc_message.insert(ipc_message.begin(), payload, payload + length);

    const auto result_message = dispatcher_.Dispatch(ipc_message);
  }
}

int ZSocketEventHandler::ReceiveAllFromSocket(int fd, uint8_t* buffer,
                                              int /*length*/) {
  int bytesRead = 0, result = 0;
  // while (bytesRead < length) {
  result = recv(fd, buffer, ZServiceDispatcher::MAX_PARAM_SERIALIZED_SIZE,
                MSG_DONTWAIT);  // NON-block
  if (result == -1)             // && errno == ??)
  {
  } else if (result <= 0) {  // 0 -> peer has performed shutdown
    TRACE("ERROR when read from socket, error: [%d]\n", errno);
    return result;
  }
  bytesRead += result;
  // }
  // TRACE("Receive from fd: [%d] completed, payload:", fd);
  // TRACE("\n%s", Hex::DumpWithAscii(buffer, length).c_str());
  return bytesRead;
}