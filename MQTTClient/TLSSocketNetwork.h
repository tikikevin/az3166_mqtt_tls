#include "TLSSocket.h"

class TLSSocketNetwork {
public:
  TLSSocketNetwork() {}

  // 1) Connect via TLS on host:port
  int connect(const char* host, int port) {
    return socket.open(host, port);
  }

  // 2) Read with timeout (ms)
  int read(uint8_t* buf, int len, int timeout) {
    return socket.recv(buf, len);
  }

  // 3) Write with timeout (ms)
  int write(uint8_t* buf, int len, int timeout) {
    return socket.send(buf, len);
  }

  // 4) Clean disconnect
  void disconnect() {
    socket.close();
  }

  // Optional: expose TLS-specific APIs
  void setCACert(const unsigned char* cert, size_t len) {
    socket.setCACert(cert, len);
  }

private:
  TLSSocket socket;
};