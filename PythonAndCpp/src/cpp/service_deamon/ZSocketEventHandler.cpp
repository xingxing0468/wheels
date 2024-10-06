#include "src/cpp/service_deamon/ZSocketEventHandler.h"

#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <filesystem>

#include "src/cpp/utils/Trace.h"

namespace {
const std::string IPC_SOCKET_NAME = "/tmp/IpcSocket";

std::string DumpWithAscii(const uint8_t* data, int size) {
  constexpr int DEFAULT_ASCII_WRAP = 0x10;
  std::string ret;
  std::string hexLine;
  std::string asciiLine;

  char tmpCharArray[4];
  char tmpAsciiArray[2];
  memset(tmpCharArray, 0, 4);
  memset(tmpAsciiArray, 0, 2);

  for (int i = 0; i < size; i++) {
    sprintf(tmpCharArray, "%02X ", data[i]);
    sprintf(tmpAsciiArray, "%c", isprint(data[i]) != 0 ? data[i] : '.');
    hexLine += tmpCharArray;
    asciiLine += tmpAsciiArray;
    memset(tmpCharArray, 0, 4);
    memset(tmpAsciiArray, 0, 2);
    if ((i + 1) % DEFAULT_ASCII_WRAP == 0) {
      ret += hexLine + "    " + asciiLine + '\n';
      hexLine.clear();
      asciiLine.clear();
    }
  }
  // deal with the rest
  int restToFill = DEFAULT_ASCII_WRAP - size % DEFAULT_ASCII_WRAP;
  if (!hexLine.empty()) {
    for (int i = 0; i < restToFill; i++) {
      hexLine += "   ";  // %2X + ' '
    }
    ret += hexLine + "    " + asciiLine + '\n';
  }
  return ret;
}
}  // namespace

ZSocketEventHandler::ZSocketEventHandler(ZEventloop& eventloop,
                                         const ZServiceDispatcher& dispatcher)
    : server_socket_name_{IPC_SOCKET_NAME},
      eventloop_{eventloop},
      dispatcher_{dispatcher} {
  Init();
}

ZSocketEventHandler::~ZSocketEventHandler() { CleanUp(); }

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

void ZSocketEventHandler::Init() {
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

    // Normally to make an anomynous socket we make the first byte as '\0'
    // But in some OS and for PY it check the length for the char '\0'
    // So it does not work,
    // Then in the cleanup we have to manually unlink the socket name
    // To avoid failure of next creation.
    // strcpy(serverAddr.sun_path + 1, this->server_socket_name_.c_str());
    strcpy(serverAddr.sun_path, this->server_socket_name_.c_str());

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

  eventloop_.AddFd(server_socket_fd_, this);
}

void ZSocketEventHandler::CleanUp() {
  if (server_accepted_fd_ != -1) {
    eventloop_.RemoveFd(server_accepted_fd_);
    server_accepted_fd_ = -1;
  }
  if (server_socket_fd_ != -1) {
    eventloop_.RemoveFd(server_socket_fd_);
    close(server_socket_fd_);
    server_socket_fd_ = -1;
  }
  std::filesystem::path socket_file{IPC_SOCKET_NAME};
  if (std::filesystem::exists(socket_file)) {
    TRACE("Clean up socket file...");
    std::filesystem::remove(socket_file);
  }
}

void ZSocketEventHandler::HandleConnect() {
  if (server_accepted_fd_ != -1) {
    TRACE("WARNING: ONLY one connection is supported now, skip...");
    return;
  }
  if ((server_accepted_fd_ = accept(server_socket_fd_, NULL, NULL)) == -1) {
    TRACE("ERROR: Accept once failed: [%d]", errno);
    return;
  }

  eventloop_.AddFd(server_accepted_fd_, this);
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
  } else if (length == 0) {
    TRACE("Client disconnected, remove accepted FD: [%d]\n",
          server_accepted_fd_);
    eventloop_.RemoveFd(server_accepted_fd_);
    server_accepted_fd_ = -1;
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
  TRACE("Receive from fd: [%d] completed, length: [%d] payload:", fd,
        bytesRead);
  TRACE("\n%s", DumpWithAscii(buffer, bytesRead).c_str());
  return bytesRead;
}