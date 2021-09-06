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
