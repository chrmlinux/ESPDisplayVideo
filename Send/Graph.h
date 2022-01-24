#include <vector>
#define LINE_COUNT 6
static std::vector<int> points[LINE_COUNT];
static int pointColors[] = { TFT_RED, TFT_GREEN, TFT_BLUE, TFT_CYAN, TFT_MAGENTA, TFT_YELLOW };
static int xoffset, yoffset, point_count;

int getBaseColor(int x, int y)
{
  return ((x ^ y) & 3 || ((x - xoffset) & 31 && y & 31) ? TFT_BLACK : ((!y || x == xoffset) ? TFT_WHITE : TFT_DARKGREEN));
}

void setupGraph(void)
{
  yoffset = canvas.height() >> 1;
  xoffset = canvas.width()  >> 1;
  point_count = canvas.width() + 1;
  for (int i = 0; i < LINE_COUNT; i++)
  {
    points[i].resize(point_count);
  }
  canvas.startWrite();
  canvas.setAddrWindow(0, 0, canvas.width(), canvas.height());
  for (int y = 0; y < canvas.height(); y++)
  {
    for (int x = 0; x < canvas.width(); x++)
    {
      canvas.writeColor(getBaseColor(x, y - yoffset), 1);
    }
  }
  canvas.endWrite();
}
void loopGraph(void)
{
/*
  static int prev_sec;
  static int fps;
  ++fps;
  int sec = millis() / 1000;
  if (prev_sec != sec)
  {
    prev_sec = sec;
    canvas.setCursor(canvas.width()-(8*8), 0);
    canvas.printf("fps:%3d", fps);
    fps = 0;
  }
*/
  static int count;
  for (int i = 0; i < LINE_COUNT; i++)
  {
    points[i][count % point_count] =
      (sinf((float)count / (10 + 30 * i)) +
       sinf((float)count / (13 + 37 * i))) * (canvas.height() >> 2);
  }
  ++count;
  canvas.startWrite();
  int index1 = count % point_count;
  for (int x = 0; x < point_count - 1; x++)
  {
    int index0 = index1;
    index1 = (index0 + 1) % point_count;
    for (int i = 0; i < LINE_COUNT; i++)
    {
      int y = points[i][index0];
      if (y != points[i][index1])
      {
        canvas.writePixel(x, y + yoffset, getBaseColor(x, y));
      }
    }
    for (int i = 0; i < LINE_COUNT; i++)
    {
      int y = points[i][index1];
      canvas.writePixel(x, y + yoffset, pointColors[i]);
    }
  }
  canvas.endWrite();
}
