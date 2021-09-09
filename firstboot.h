

void generateConfig(const char *filename){
  SPIFFS.remove(filename);
  // Open file for writing
  File file = SPIFFS.open(filename, FILE_WRITE);
  if (!file) {
    Serial.println(F("Failed to create file"));
    return;
  }

  DynamicJsonDocument  doc(200);

  // Set the values in the document
  JsonObject root = doc.to<JsonObject>();
  root["hostname"] = "ESP32DMX";
  root["port"] = "80";
  JsonObject wifi = root.createNestedObject("wifi");
  wifi["ssid"] = "Weissig2011";
  wifi["password"] = "VereinsHaus";
  JsonObject edit = root.createNestedObject("edit");
  edit["username"] = "admin";
  edit["password"] = "admin";
  // Serialize JSON to file
  if (serializeJsonPretty(doc, file) == 0) {
    Serial.println(F("Failed to write to file"));
  }

  // Close the file
  file.close();
}
