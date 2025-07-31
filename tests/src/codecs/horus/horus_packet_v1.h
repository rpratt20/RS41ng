#ifndef __HORUS_PACKET_V1_H
#define __HORUS_PACKET_V1_H

#include <stdint.h>
#include <stdlib.h>
#include "telemetry.h"

// Horus Binary v1 Packet Format
// See: https://github.com/projecthorus/horusdemodlib/wiki/4-Packet-Format-Details#horus-binary-v1-22-bytes
// Note that we need to pack this to 1-byte alignment, hence the #pragma flags below
// Refer: https://gcc.gnu.org/onlinedocs/gcc-4.4.4/gcc/Structure_002dPacking-Pragmas.html
#pragma pack(push, 1)
typedef struct _horus_packet_v1 {
    uint8_t PayloadID;  // Payload ID (0-255)
    uint16_t Counter; // Sequence number
    uint8_t Hours; // Time of day, Hours
    uint8_t Minutes; // Time of day, Minutes
    uint8_t Seconds; // Time of day, Seconds
    float Latitude; // Latitude in degrees
    float Longitude; // Longitude in degrees
    uint16_t Altitude; // Altitude in meters
    uint8_t Speed; // Speed in km/h (although spec says: Knots (1-255 knots))
    uint8_t Sats; // Number of GPS satellites visible
    int8_t Temp; // Temperature in Celsius, as a signed value (-128 to +128, though sensor limited to -64 to +64 deg C)
    uint8_t BattVoltage; // 0 = 0v, 255 = 5.0V, linear steps in-between.
    uint16_t Checksum; // CRC16-CCITT Checksum.
} horus_packet_v1;  //  __attribute__ ((packed)); // Doesn't work?
#pragma pack(pop)

size_t horus_packet_v1_create(uint8_t *payload, size_t length, telemetry_data *data, uint8_t payload_id);

#endif
