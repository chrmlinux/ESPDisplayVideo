#define _M5DISPLAY_H_
class M5Display {};

//#include <M5Stack.h>
//#include <M5StickC.h>
//#include <M5Atom.h>

#include <LovyanGFX.hpp>
static LGFX_Sprite canvas;

#include "ESP_8_BIT_composite.h"
ESP_8_BIT_composite video(true /* = NTSC */);

#define VIDEO_WIDTHMAX  (256)
#define VIDEO_HEIGHTMAX (240)
#define VIDEO_SIZEMAX   (VIDEO_WIDTHMAX * VIDEO_HEIGHTMAX)
#define VIDEO_LEFT      (  3)
#define VIDEO_RIGHT     ( 13)
#define VIDEO_TOP       ( 10)
#define VIDEO_BOTTOM    (  6)
#define VIDEO_BOXEL     (  8)
#define VIDEO_WIDTH     (VIDEO_WIDTHMAX - VIDEO_LEFT - VIDEO_RIGHT)
#define VIDEO_HEIGHT    (VIDEO_HEIGHTMAX - VIDEO_TOP - VIDEO_BOTTOM)
#define VIDEO_SIZE      (VIDEO_WIDTH * VIDEO_HEIGHT)
#define VIDEO_DRAW_DELAY  (8)
#define UDP_MAX_BYTE    (1436)
#define UDP_RAW         (VIDEO_SIZE / UDP_MAX_BYTE)
#define UDP_MOD         (VIDEO_SIZE % UDP_MAX_BYTE)
#define UDP_DELAY       (1)
#define UDP_PORT        (10000)

static uint16_t _transByte = 0;

/*
  (+0,+0)
  +-------------------------------------------------------+
  | (+3,+10)                                                |
  |    +-------------------------------------------- +    |
  |    |                                             |    |
  |    |                                             |    |
  |    |                                             |    |
  |    |                                             |    |
  |    |                                             |    |
  |    |                                             |    |
  |    |          canvasBuffer [240x224xRGB332]      |    |
  |    +---------------------------------------------+    |
  |            frameBufferLine [256x240xRGB332]  (-13, -6)|
  +-------------------------------------------------------+
                                                      (-0, -0)

          frameBufferLine 256 x 240 x 1 = 61,440 byte used
          canvasBuffer    240 x 228 x 1 = 53,760 byte used
          ------------------------------------------------
                                           7,680 byte free
*/

// ===================================================
//
// setupVideo
//
// ===================================================
void setupVideo()
{
  video.begin();
}

// ===================================================
//
// getFps
//
// ===================================================
uint32_t getFps()
{
  static uint32_t psec = 0;
  static uint32_t cnt = 0;
  static uint32_t fps = 0;
  uint32_t sec = 0;

  sec = millis() / 1000;
  ++ cnt;
  if (psec != sec) {
    psec = sec;
    fps = cnt;
    cnt = 0;
  }
  return fps;
}

// ===================================================
//
// dispFps
//
// ===================================================
void dispFps() {
  canvas.setTextColor(TFT_WHITE);
  canvas.setCursor(0, VIDEO_HEIGHT - canvas.fontHeight());
  canvas.printf("Thx.@Regorlas/Lovyan03/lang-ship %3dfps",  getFps());
}

// ===================================================
//
// clearCanvas
//
// ===================================================
void clearCanvas(uint32_t col)
{
  canvas.fillScreen(col);
}

// ===================================================
//
// setupCanvas
//
// ===================================================
void setupCanvas() {
  canvas.setColorDepth(sizeof(uint8_t) << 3);
  canvas.createSprite(VIDEO_WIDTH, VIDEO_HEIGHT);
  canvas.fillScreen(TFT_BLACK);
//    canvas.setFont(&lgfxJapanMincho_8); // Japanese font ready !
  canvas.setFont(&fonts::Font0);
}
