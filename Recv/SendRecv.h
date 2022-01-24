#include <WiFi.h>
#include <AsyncUDP.h>
AsyncUDP udp;
#define UDPMAX ( 1436 )

#define APSSID      "ESPDispley"
#define APPSK       "#ESPDispley#"
#define HOSTNAME    "ESPDispley"
enum {SOH = 0x01, STX, ETX};

volatile static bool _dispEnable = false;

// ===================================================
//
// setupAsyncUDP
//
// ===================================================
void setupAsyncUDP()
{
  IPAddress ip(192, 168, 4,  1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(ip, ip, subnet);
  WiFi.softAP(APSSID, APPSK);
  Serial.println("UDP ready");
  if (udp.listen(UDP_PORT)) {
    udp.onPacket([](AsyncUDPPacket packet) {

      static bool stat = false;
      uint8_t *recv = packet.data();
      int recvLen = packet.length();

//      digitalWrite(LEDPIN, !stat);
      //      Serial.printf("[recv] recvLen %d\n", recvLen);
      switch (recvLen) {
        case 1:
          if (recv[0] == STX) {
            _recvAryLen = 0;
            _dispEnable = false;
            memset(_recvAry, 0x0, VIDEO_SIZE);
          } else {
            //            Serial.printf("[recv] _recvAryLen %d\n", _recvAryLen);
            _dispEnable = true;
          }
          break;
        default:
          memcpy(&_recvAry[_recvAryLen], recv, recvLen);
          _recvAryLen += recvLen;
          break;
      }
      stat = !stat;
    });
  }
}
