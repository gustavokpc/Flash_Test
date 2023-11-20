/* RADIO DEFINES */

#define LORA_BANDWIDTH LORA_BW_031              // details in SX1276::BandwidthMap
#define LORA_SPREADING_FACTOR LORA_SF10
#define LORA_CODINGRATE LORA_CR_4_5
#define LORA_DATARATE LORA_DATARATE_2048    // In 2048, should change in the future
#define LORA_FIX_LEN false
#define LORA_ENABLE_CRC true
#define LORA_ENABLE_FHSS false
#define LORA_FHSS_PERIOD 4
#define LORA_PREAMBLE_LENGTH 0x8
#define LORA_INVERT_IQ false
#define LORA_TIMEOUT_PERIOD 2000 // ms
#define TX_OUTPUT_POWER 20 // dBm

#define RF_FREQUENCY 915e6 // Hz

/* GLOBAL POSITIONING DEFINES */

#define GPS_EN
#define GPS_UART
#define GPS_TIMEOUT 100 //In ms

#ifdef GPS_EN
#ifdef GPS_UART
/* GPS UBLOX DEFINES (UART) */

#define GPS_TX PB_6
#define GPS_RX PB_7
#define GPS_BAUDRATE 9600
#else
/* GPS UBLOX DEFINES (I2C) */
#define GPS_SDA PA_11
#define GPS_SCL PA_12

#endif
#endif

/* STORAGE DEFINES */
/* FLASH SPI INTERFACE */

#define FLASH_EN
#define FLASH_MOSI  PA_7
#define FLASH_MISO  PA_6
#define FLASH_SCLK  PA_5
#define FLASH_CS    PA_4

/* SD CARD SPI INTERFACE */ 

#define SD_EN
#define SD_MOSI     PC_1
#define SD_MISO     PC_2
#define SD_SCLK     PB_10
#define SD_CS       PA_9

// #define FORCE_REFORMAT_FLASH
// #define FORCE_REFORMAT_SD

/* PRINT OPTION DEFINES */

#define DEBUG_MESSAGES
#define DEBUG_NMEA_MESSAGES
#define FILE_PRINT

// If debug messages are active, debugPrint is used as printf, otherwise it
// will be treated as an empty function
#ifdef DEBUG_MESSAGES
#define debugPrint(...) printf(__VA_ARGS__)
#else
#define debugPrint(...)
#endif

// If NMEA debug messages are active, when the uC retrieves messages from the GPS
// it will print the NMEA messages it got.
#ifdef DEBUG_NMEA_MESSAGES
#define debugPrintNMEA(...) printf(__VA_ARGS__)
#else
#define debugPrintNMEA(...)
#endif 

#ifdef FILE_PRINT
#define filePrint(...) printf(__VA_ARGS__)
#else
#define filePrint(...)
#endif
