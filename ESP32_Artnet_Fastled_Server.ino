/*
   
*/

// wifi ssid and password should be added to a file in the sketch named secrets.h
// the secrets.h file should be added to the .gitignore file and never committed or
// pushed to public source control (GitHub).
// const char* ssid = "........";
// const char* password = "........";
//  #define TOKEN "token_............." // Set your Beebotte channel token


#include <FastLED.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <SPIFFS.h>

#include <ESPAsyncWebServer.h>
#include <SPIFFSEditor.h>
#include <DNSServer.h>
#include <FS.h>

#include <AsyncElegantOTA.h>

AsyncWebServer webServer(80);


const int led = 2;

uint8_t power = 1;


uint8_t brightness = 128;
uint8_t speed = 5;



CRGB solidColor = CRGB::Blue;



#define DATA_PIN    0
#define CLK_PIN   5



#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_STRIPS 1
#define NUM_LEDS_PER_STRIP 12
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS
CRGBArray<NUM_LEDS> leds;

#define MILLI_AMPS         500 // IMPORTANT: set the max milli-Amps of your power supply (4A = 4000mA)
#define FRAMES_PER_SECOND  120




#include "secrets.h"
#include "wifi.h"
#include "web.h"
#include "includes.h"










void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);

  //  delay(3000); // 3 second delay for recovery
  Serial.begin(115200);

  SPIFFS.begin();

  
  setupWiFi();


  // three-wire LEDs (WS2811, WS2812, NeoPixel)
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS);

  // set master brightness control
  FastLED.setBrightness(brightness);

  

  initTest();
}

void loop()
{
  handleWeb();
  AsyncElegantOTA.loop();
  FastLED.show();
  
}
