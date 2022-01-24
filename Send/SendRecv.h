#include <WiFi.h>
#include <AsyncUDP.h>
AsyncUDP udp;

#define APSSID      "ESPDispley"
#define APPSK       "#ESPDispley#"
#define HOSTNAME    "ESPDispley"
enum {SOH = 0x01, STX, ETX};
bool _transEnable = false;

void fakedelay(int tm)
{
}

// ===================================================
//
// setupAsyncUDP
//
// ===================================================
void setupAsyncUDP()
{
  Serial.begin(115200);
  WiFi.begin(APSSID, APPSK);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("UDP Failed");
    while (1) {}
  }
  if (udp.connect(IPAddress(192, 168, 4, 1), UDP_PORT)) {
    Serial.println("UDP connected");
    //    udp.onPacket([](AsyncUDPPacket packet) {
    //    });
  }
}

// ===================================================
//
// sendScrn
//
// ===================================================
void sendScrn()
{
  //  digitalWrite(LEDPIN, !stat);
  _transByte = VIDEO_SIZE;

  uint8_t dt[2] = {STX, ETX};
  uint16_t sendByte = 0;
  int row = UDP_RAW;
  int mod = UDP_MOD;

  uint8_t *transAry = (uint8_t *)canvas.getBuffer();

  udp.write(&dt[0], 1);
  delay(UDP_DELAY);
  for (register int i = 0; i < row; i++) {
    udp.write(&transAry[sendByte], UDP_MAX_BYTE);
    delay(UDP_DELAY);
    sendByte += UDP_MAX_BYTE;
  }
  if (mod) {
    udp.write(&transAry[sendByte], mod);
    delay(UDP_DELAY);
    sendByte += mod;
  }
  udp.write(&dt[1], 1);
  delay(UDP_DELAY);

  delay(VIDEO_DRAW_DELAY);
}
