/**
 * Address of the version data. This should never change between versions.
 */
#define EEPROM_ADDR_VERSION_DATE 0x0

/**
 * Your data should start after this location.
 * On gcc, __DATE_ is 11 chars long, __TIME__ is 8
 */
#define EEPROM_ADD_START_OF_DATA 0x13

/**
* Determine if this is the first power-up after
* fresh program was loaded into the flash.
*/
boolean is_initial_program_load()
{
    const String version_date = __DATE__ __TIME__;
    uint16_t len = version_date.length();
    boolean is_ipl = false;

    for (unsigned int i = 0; i < len; i++) {
        int addr = EEPROM_ADDR_VERSION_DATE + i;

        if (EEPROM.read(addr) != version_date[i]) {
            EEPROM.write(addr, version_date[i]);
            is_ipl = true;
        }
    }

    return is_ipl;
}

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
