//#define MODEPIN (37)
//#define RSTPIN  (39)
//#define LEDPIN  (10)

#include "Video.h"
#include "SendRecv.h"

// ===================================================
//
// setup
//
// ===================================================
void setup()
{
  setCpuFrequencyMhz(240);
  Serial.begin( 115200 );
  setupAsyncUDP();
  setupVideo();
//  pinMode(MODEPIN, INPUT_PULLUP);
//  pinMode(RSTPIN, INPUT_PULLUP);
//  pinMode(LEDPIN, OUTPUT);
//  digitalWrite(LEDPIN, !LOW);
}

// ===================================================
//
// loop
//
// ===================================================
void loop()
{
//  if (!digitalRead(RSTPIN)) ESP.restart();
  if (_dispEnable) dispVideo();
  delay(1);
}
