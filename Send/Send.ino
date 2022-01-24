/*

  +---------------------+                       +---------------------+
  | LovyanGFX Sprite    |                       |ESP_8_BIT_composite  |
  | 256 x 240 x RGB332  | canvas.getBuffer      |256 x 240 x RGB332   |
  |                     | **getFrameBufferLines |                     |
  |                     |            =>         |                     |
  |                     |                       | G26(RCA)            |
  |                     |                       | GND                 |
  |                     |                       |                     |
  +---------------------+                       +---------------------+

  #### caution ####
  edit ESP_8_BIT_composite.cpp:25   #define USE_DAC_CH (DAC_CHANNEL_2)
  edit ESP_8_BIT_composite.cpp:116  dac_output_enable (USE_DAC_CH);
  edit ESP_8_BIT_composite.cpp:687  dac_output_disable(USE_DAC_CH);

*/

#define MODEPIN (39)
#define RSTPIN  (39)
#define LEDPIN  (10)

#include "Video.h"
#include "Draw.h"
#include "SendRecv.h"
#include "Graph.h"

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
  setupCanvas();
  pinMode(MODEPIN, INPUT_PULLUP);
  pinMode(RSTPIN, INPUT_PULLUP);
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, !LOW);

  setupGraph();
}

// ===================================================
//
// loop
//
// ===================================================
void loop()
{
  if (!digitalRead(RSTPIN)) ESP.restart();
  // loopGraph();
  // pingPong();
   textRain(30, 28, 8);
  drawInfo();
  sendScrn();
  delay(1);
}
