#include "packet.h"
int main() {
  Packet* p = nullptr;
  p = new IPv4Packet("192.168.0.1", "192.168.0.1", "00000000001111111111");
  p->Segment(30);
  delete p;
  p = new IPv6Packet("1080::0008:0800:200c:417a", "1080::0008:0800:200c:417a",
    "00000000001111111111");
  p->Segment(30);
  delete p;
  return 0;
}
