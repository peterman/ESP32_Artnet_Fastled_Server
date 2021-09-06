
void setupWeb() {
  webServer.serveStatic("/", SPIFFS, "/").setDefaultFile("index.htm").setCacheControl("max-age=600");
  
  webServer.onNotFound([](AsyncWebServerRequest * request) { 
        request->send(404, "text/plain", "Not found");
  });

  webServer.on("/heap", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(ESP.getFreeHeap()));
  });
  
  Serial.println ( "Starting Editorhandler" );
  webServer.addHandler(new SPIFFSEditor(SPIFFS, editor_username, editor_password));
  Serial.println ( "Starting OTA-Handler" );
  AsyncElegantOTA.begin(&webServer);    // Start ElegantOTA
  Serial.println ( "Starting HTTP server" );
  webServer.begin();
  Serial.println ( "HTTP server started" );
}
