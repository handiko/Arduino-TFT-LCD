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

#define TFT_CS 0
#define TFT_RST 13
#define TFT_DC 2
#define TFT_MOSI 14
#define TFT_SCLK 12
#define TFT_MISO -1

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST, TFT_MISO);

#define BORDER_WIDTH 5
#define BOX_WIDTH (ILI9341_TFTWIDTH - (2 * BORDER_WIDTH))
#define BOX_HEIGHT ((ILI9341_TFTHEIGHT - (4 * BORDER_WIDTH)) / 3)

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHT11 11

// DHT data pin = IO4 --> 4
DHT dht11(4, DHT11, 1);

float last_temp, last_hum, last_hi;
float temp, hum, hi;

void setup()
{
  // put your setup code here, to run once:
  tft.begin();
  dht11.begin();

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
  dht11.read();

  temp = dht11.readTemperature();
  hum = dht11.readHumidity();
  hi = dht11.computeHeatIndex(false);

  if (temp != last_temp)
  {
    tft.setCursor(3 * BORDER_WIDTH, 5 * BORDER_WIDTH + 60);
    tft.fillRect(3 * BORDER_WIDTH, 50, BOX_WIDTH - 3 * BORDER_WIDTH, 40, ILI9341_DARKCYAN);
    tft.print(dht11.readTemperature(), 1);
    tft.print(F(" C"));
  }

  if (hum != last_hum)
  {
    tft.setCursor(3 * BORDER_WIDTH, 6 * BORDER_WIDTH + 60 + BOX_HEIGHT);
    tft.fillRect(3 * BORDER_WIDTH, 50 + BORDER_WIDTH + BOX_HEIGHT, BOX_WIDTH - 3 * BORDER_WIDTH, 40, ILI9341_DARKCYAN);
    tft.print(dht11.readHumidity(), 1);
    tft.print(F(" %"));
  }

  if (hi != last_hi)
  {
    tft.setCursor(3 * BORDER_WIDTH, 7 * BORDER_WIDTH + 60 + 2 * BOX_HEIGHT);
    tft.fillRect(3 * BORDER_WIDTH, 50 + 2 * BORDER_WIDTH + 2 * BOX_HEIGHT, BOX_WIDTH - 3 * BORDER_WIDTH, 40, ILI9341_DARKCYAN);
    tft.print(dht11.computeHeatIndex(false), 1);
    tft.print(F(" C"));
  }

  last_temp = temp;
  last_hum = hum;
  last_hi = hi;

  delay(5000);
}