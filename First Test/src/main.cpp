/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <Arduino.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

/*
TFT DISPLAY PINS          ARDUINO PINS
    VCC                       5V
    GND                       GND
    CS                        9
    RST                       7
    DC                        8
    MOSI                      11
    SCK                       13
    LED                       5V
    MISO                      --
*/

#define TFT_CS 9
#define TFT_RST 7
#define TFT_DC 8
#define TFT_MOSI 11
#define TFT_SCLK 13
#define TFT_MISO -1

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST, TFT_MISO);

#define COLOR_NUM 19
unsigned int color[COLOR_NUM] = {
    ILI9341_BLACK,
    ILI9341_NAVY,
    ILI9341_DARKGREEN,
    ILI9341_DARKCYAN,
    ILI9341_MAROON,
    ILI9341_PURPLE,
    ILI9341_OLIVE,
    ILI9341_LIGHTGREY,
    ILI9341_DARKGREY,
    ILI9341_BLUE,
    ILI9341_GREEN,
    ILI9341_CYAN,
    ILI9341_RED,
    ILI9341_MAGENTA,
    ILI9341_YELLOW,
    ILI9341_WHITE,
    ILI9341_ORANGE,
    ILI9341_GREENYELLOW,
    ILI9341_PINK};

void setup()
{
  tft.begin();

  tft.fillScreen(ILI9341_BLACK);

  tft.setRotation(2);

  tft.drawCircle(ILI9341_TFTWIDTH / 2, 25, 25, ILI9341_BLUE);
  tft.fillRect(ILI9341_TFTWIDTH / 2, 30, 30, 40, ILI9341_RED);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.writeFastHLine(100,10,10,ILI9341_RED);
  tft.print(F("Hello World"));
}

void loop()
{
  for (int i = 0; i < ILI9341_TFTHEIGHT; i++)
  {
    tft.scrollTo(i);

    delay(20);
  }
}