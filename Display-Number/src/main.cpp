#include <Arduino.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>

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

#define BORDER_WIDTH 5
#define BOX_WIDTH (ILI9341_TFTWIDTH - (2 * BORDER_WIDTH))
#define BOX_HEIGHT ((ILI9341_TFTHEIGHT - (4 * BORDER_WIDTH)) / 3)

void setup()
{
  // put your setup code here, to run once:
  tft.begin();

  tft.setRotation(2);

  tft.fillRect(0, 0, ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT, ILI9341_BLACK);

  tft.fillRect(BORDER_WIDTH, BORDER_WIDTH, BOX_WIDTH, BOX_HEIGHT, ILI9341_DARKCYAN);
  tft.fillRect(BORDER_WIDTH, 2 * BORDER_WIDTH + BOX_HEIGHT, BOX_WIDTH, BOX_HEIGHT, ILI9341_DARKCYAN);
  tft.fillRect(BORDER_WIDTH, 3 * BORDER_WIDTH + 2 * BOX_HEIGHT, BOX_WIDTH, BOX_HEIGHT, ILI9341_DARKCYAN);

  tft.setTextColor(ILI9341_WHITE, ILI9341_DARKCYAN);

  tft.setFont(&FreeSansBold9pt7b);
  tft.setCursor(3 * BORDER_WIDTH, 5 * BORDER_WIDTH);
  tft.print(F("Temperature :"));

  tft.setFont(&FreeSansBold9pt7b);
  tft.setCursor(3 * BORDER_WIDTH, 6 * BORDER_WIDTH + BOX_HEIGHT);
  tft.print(F("Rel. Humidity :"));

  tft.setFont(&FreeSansBold9pt7b);
  tft.setCursor(3 * BORDER_WIDTH, 7 * BORDER_WIDTH + 2 * BOX_HEIGHT);
  tft.print(F("Heat Index :"));

  tft.setFont(&FreeSansBold24pt7b);
}

void loop()
{
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 1000; i++)
  {
    tft.setCursor(3 * BORDER_WIDTH, 5 * BORDER_WIDTH + 60);
    tft.fillRect(3 * BORDER_WIDTH, 50, BOX_WIDTH - 3 * BORDER_WIDTH, 40, ILI9341_DARKCYAN);
    tft.print(rand(), 1);
    tft.print(F(" C"));

    tft.setCursor(3 * BORDER_WIDTH, 6 * BORDER_WIDTH + 60 + BOX_HEIGHT);
    tft.fillRect(3 * BORDER_WIDTH, 50 + BORDER_WIDTH + BOX_HEIGHT, BOX_WIDTH - 3 * BORDER_WIDTH, 40, ILI9341_DARKCYAN);
    tft.print(rand(), 1);
    tft.print(F(" %"));

    tft.setCursor(3 * BORDER_WIDTH, 7 * BORDER_WIDTH + 60 + 2 * BOX_HEIGHT);
    tft.fillRect(3 * BORDER_WIDTH, 50 + 2 * BORDER_WIDTH + 2 * BOX_HEIGHT, BOX_WIDTH - 3 * BORDER_WIDTH, 40, ILI9341_DARKCYAN);
    tft.print(rand(), 1);
    tft.print(F(" C"));

    delay(5000);
  }
}