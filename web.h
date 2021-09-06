/*
   Modifed 2019 by Jeremy Spencer
   
   Ported from ESP32 FastLED WebServer: https://github.com/jasoncoon/esp32-fastled-webserver
   Copyright (C) 2017 Jason Coon

   Built upon the amazing FastLED work of Daniel Garcia and Mark Kriegsman:
   https://github.com/FastLED/FastLED

   ESP32 support provided by the hard work of Sam Guyer:
   https://github.com/samguyer/FastLED

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

void setupWeb() {
  webServer.serveStatic("/", SPIFFS, "/").setDefaultFile("index.htm").setCacheControl("max-age=600");

  webServer.on("/all", HTTP_GET, [](AsyncWebServerRequest * request) {
    String json = "ALL";
    request->send(200, "text/json", json);
  });

// webServer.onRequestBody([](AsyncWebServerRequest *request){
  webServer.onNotFound([](AsyncWebServerRequest * request) { //Hacky - but works ;)
        request->send(404);
  });
  
  Serial.println ( "Starting Editorhandler" );
  webServer.addHandler(new SPIFFSEditor(SPIFFS, editor_username, editor_password));
  AsyncElegantOTA.begin(&webServer);    // Start ElegantOTA
  Serial.println ( "Starting HTTP server" );
  webServer.begin();
  Serial.println ( "HTTP server started" );



  Serial.println("Ready");
  if (!apMode) {
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

void handleWeb() {
  static bool webServerStarted = false;
  if (!apMode) {
    // check for connection
    if ( WiFi.status() == WL_CONNECTED ) {
      if (!webServerStarted) {
        // turn off hte board's LED when connected to wifi
        digitalWrite(led, 1);
        Serial.println();
        webServerStarted = true;
        setupWeb();
      }
//      ArduinoOTA.handle();
    } else {
      // blink the board's LED while connecting to wifi
      static uint8_t ledState = 0;
      EVERY_N_MILLIS(125) {
        ledState = ledState == 0 ? 1 : 0;
        digitalWrite(led, ledState);
        Serial.print (".");
      }
    }
  } else {
    if (!webServerStarted) {
      setupWeb();
      webServerStarted = true;
    } else {
      dnsServer.processNextRequest();
//      ArduinoOTA.handle();
    }
  }
}
