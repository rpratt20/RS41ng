#ifndef __TELEMETRY_H
#define __TELEMETRY_H

#include <stdint.h>
#include <stdbool.h>

#include "config.h"
#include "gps.h"

typedef struct _telemetry_data {
    uint16_t data_counter;

    uint16_t battery_voltage_millivolts;
    uint16_t button_adc_value;
    int32_t internal_temperature_celsius_100;

    int32_t temperature_celsius_100;
    uint32_t pressure_mbar_100;
    uint32_t humidity_percentage_100;
    uint16_t pulse_count;
    float radiation_intensity_uR_h;

    gps_data gps;

    char locator[LOCATOR_PAIR_COUNT_FULL * 2 + 1];

    int	clock_calibration_trim;
    uint16_t clock_calibration_count;
// RP added
    uint8_t rp_cutdown;
    uint8_t rp_xtal_code;
    uint8_t rp_lu_code;
} telemetry_data;

void telemetry_collect(telemetry_data *data);

extern int8_t gps_time_leap_seconds;

#endif
