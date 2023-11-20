#include <stdint.h>

#ifndef DATA_H_
#define DATA_H_
struct Data
{
  // preamble for signaling beginning of the frame and alignment/synchronization
  const uint8_t preamble[7] = {'J', 'U', 'P', 'I', 'T', 'E', 'R'};
  uint8_t header;               // Header for identification of updated informations
  int32_t ag[3];                // Acceleration of the accelerometer and gyroscope LSM6DSL
  int32_t w[3];                 // Angular velocity of LSM6DSL
  int32_t a[3];                 // Acceleration of the accelerometer LSM303AGR
  int32_t m[3];                 // Heading of LSM303AGR
  float pressure;               // Pressure of LPS22HB
  float temperatureLPS22HB;     // Temperature from LPS22HB
  float humidity;               // Humidity of HTS221
  float temperatureHTS221;      // Temperature from HTS221
  uint8_t gpsFix;               // GPS fix
  float latitude;               // GPS Latitude
  float longitude;              // GPS Longitude
  float elevation;              // GPS Elevation (MSL)
  float speed;                  // GPS speed
  uint8_t numbSat;              // GPS number of satellites conected
  uint32_t UTCTime;             // GPS UTC Time
  uint32_t UTCDate;             // GPS UTC Date
  uint64_t timeStamp;           // Timestamp in ms from start of package sending
};
#endif
