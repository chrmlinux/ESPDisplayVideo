void drawInfo()
{
  canvas.setCursor(0, 0);
  canvas.printf("%3dx%3d %3dfps", VIDEO_WIDTH, VIDEO_HEIGHT, getFps());
}

// ===================================================
//
// pingPong
//
// ===================================================
void pingPong()
{
  
  clearCanvas(TFT_BLACK);
  uint16_t stp = 8;
  uint16_t hstp = stp / 2;
  static int16_t x = 0;
  static int16_t y = 0;
  static uint16_t r = 0;
  static int16_t lx = stp;
  static int16_t ly = stp;
  static int16_t pos = 0;
  static int16_t lp = 1;

  for (int x = 0; x < VIDEO_WIDTH;  x += stp) {
    canvas.drawLine(pos + x, 0, pos + x, VIDEO_HEIGHT - 1, TFT_BLUE);
  }
  for (int y = 0; y < VIDEO_HEIGHT; y += stp) {
    canvas.drawLine(0, pos + y, VIDEO_WIDTH - 1, pos + y, TFT_BLUE);
  }

  if ((x > VIDEO_WIDTH) || (x < 0)) lx = lx * -1;
  if ((y > VIDEO_HEIGHT) || (y < 0)) ly = ly * -1;
  x = x + lx;
  y = y + ly;
  canvas.drawLine(x + hstp, 0, x + hstp, VIDEO_HEIGHT - 1, TFT_GREEN);
  canvas.drawLine(0, y + hstp, VIDEO_WIDTH - 1, y + hstp, TFT_GREEN);
  canvas.fillRect(x + 1, y + 1, stp - 1, stp - 1, TFT_RED);

  canvas.drawCircle(x, y, r, TFT_CYAN);
  r = (r + 1) %  VIDEO_HEIGHT;
}

// =============================================================
// textRain
// -------------------------------------------------------------
// usage textRain(column(1..40), row(1..max), fontheight(1..max)
// =============================================================
void px(int x, int y, int h, int c) {
  canvas.setTextColor(canvas.color888(0, c, 0));
  canvas.setCursor(x * h, y * h);
  canvas.printf("%c", random(0x21, 0x7e));
}
void textRain(int x, int y, int h) {
  clearCanvas(TFT_BLACK);
  static int yp[40] = {1};
  for (int i = 0; i < x; i++) {
    px(i, yp[i], h, 0xff);
    int p = 0;
    for (int j = yp[i] - y; j < yp[i]; j++) {
      px(i, j, h, (p << 3));
      p++;
    }
    if (yp[i] > y) {
      if (random(1000) > 975) yp[i] = 0;
    }
    yp[i]++;
  }
}
