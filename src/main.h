#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
#include <RH_ASK.h>
#include "/home/alan/PlatformIO/Projects/Globals/ask.h"


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define OLED_RESET -1

// 433MHz ASK TX/RX modules
#define PTT     D0
#define TXW     D5
#define RXW     D7
// Software serial comms port (for UBLOX Neo7)
// #define RXD1    D6
// #define TXD1    D7
#define LED_RED D4

RH_ASK driver(BAUD_RATE, RXW, TXW, PTT, false);

packet pkt;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);