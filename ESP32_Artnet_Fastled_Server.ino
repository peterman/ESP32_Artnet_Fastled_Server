

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
#include <ArduinoJson.h>
#include <AsyncElegantOTA.h>

#include <ArtnetWifi.h>

AsyncWebServer webServer(80);

WiFiUDP UdpSend;
ArtnetWifi artnet;
uint8_t universe = 1;  // 0 - 15


const int led = 2;

uint8_t power = 1;


uint8_t brightness = 128;
uint8_t speed = 5;

struct Config {
  char hostname[64];
  char ssid[32];
  char password[32];
  int port;
};

const char *filename = "/config.json";  
Config config;                         // <- global configuration object



CRGB solidColor = CRGB::Blue;



#define DATA_PIN    0
#define CLK_PIN   5



#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_STRIPS 1
#define NUM_LEDS_PER_STRIP 12
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS
CRGB leds[NUM_LEDS];

#define MILLI_AMPS         500 // IMPORTANT: set the max milli-Amps of your power supply (4A = 4000mA)
#define FRAMES_PER_SECOND  120



#include "firstboot.h"
#include "secrets.h"
#include "wifi.h"
#include "web.h"
#include "includes.h"


void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)
{
  bool tail = false;
  
//  Serial.print("DMX: Univ: ");
//  Serial.print(universe, DEC);
//  Serial.print(", Seq: ");
//  Serial.print(sequence, DEC);
//  Serial.print(", Data (");
//  Serial.print(length, DEC);
//  Serial.print("): ");
//  
//  if (length > 8) {
//    length = 8;
//    tail = true;
//  }
//  // send out the buffer
//  for (int i = 0; i < length; i++)
//  {
//    Serial.print(data[i]);
//    Serial.print(" ");
//  }
//  if (tail) {
//    Serial.print("...");
//  }
//  Serial.println();
  FastLED.setBrightness(data[0]);
  fill_solid( leds, NUM_LEDS, CRGB(data[1],data[2],data[3])); 

  FastLED.show();
}







void setup() {
  
  //  delay(3000); // 3 second delay for recovery
  Serial.begin(115200);
  SPIFFS.begin();
  if (is_initial_program_load() == true) {
    Serial.println(F("generate new Config"));
    generateConfig(filename);
  }
  setupWiFi();
  // three-wire LEDs (WS2811, WS2812, NeoPixel)
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS);
  // set master brightness control
  FastLED.setBrightness(brightness);
  // this will be called for each packet received
  artnet.setArtDmxCallback(onDmxFrame);
  artnet.begin();
  
  initTest();
  setupWeb();
}

void loop()
{
  AsyncElegantOTA.loop();
  //FastLED.show();
  // we call the read function inside the loop
  artnet.read();
}
