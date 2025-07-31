#include "telemetry.h"
#include "hal/system.h"
#include "drivers/ubxg6010/ubxg6010.h"
#include "drivers/pulse_counter/pulse_counter.h"
#include "bmp280_handler.h"
#include "radsens_handler.h"
#include "locator.h"
#include "config.h"
#include "log.h"

#ifdef RS41
#include "drivers/si4032/si4032.h"
#endif

#ifdef DFM17
#include "hal/clock_calibration.h"
#include "drivers/si4063/si4063.h"
#include "cap_look.h"
uint8_t clock_crystal_calibration_capacitance;
uint8_t c_t_look;
int t_look;
#endif

// Initialize leap seconds with a known good value
int8_t gps_time_leap_seconds = GPS_TIME_LEAP_SECONDS;

static bool gps_power_saving_enabled = false;

void telemetry_collect(telemetry_data *data)
{
    log_info("Collecting telemetry...\n");

    data->button_adc_value = system_get_button_adc_value();
    data->battery_voltage_millivolts = system_get_battery_voltage_millivolts();
#ifdef RS41
    data->internal_temperature_celsius_100 = si4032_read_temperature_celsius_100();
#endif
#ifdef DFM17
    data->internal_temperature_celsius_100 = si4063_read_temperature_celsius_100();
#endif

    if (bmp280_enabled) {
        bmp280_read_telemetry(data);
    }

    if (radsens_enabled) {
        radsens_read_telemetry(data);
    }

    if (pulse_counter_enabled) {
        data->pulse_count = pulse_counter_get_count();
    }

    ubxg6010_get_current_gps_data(&data->gps);

    if (GPS_HAS_FIX(data->gps)) {
        // If we have a good fix, we can enter power-saving mode
        if ((data->gps.satellites_visible >= 6) && !gps_power_saving_enabled) {
            #if GPS_POWER_SAVING_ENABLE
            ubxg6010_enable_power_save_mode();
            gps_power_saving_enabled = true;
            #endif
        }

        // If we get the number of leap seconds from GPS data, use it
        if (data->gps.leap_seconds > 0) {
            gps_time_leap_seconds = data->gps.leap_seconds;
        }
 
       #ifdef DFM17
           // SET CUTDOWN HERE FOR DFM STALK SWITCH_______________ Added RP
           // Set cutdown parameters here.       
           // If moving North Lat increases, if moving East Lon increases. Set in accordance with predicted motion.
           // Altitude can be independent as desired and set.
           if (data->gps.altitude_mm / 1000 < (CUTDOWN_ALTITUDE - 1000)) {
              system_set_cutdown(!CUT_ENABLED);
              data->rp_cutdown = 0;
           }
           else {
              if (data->gps.latitude_degrees_1000000 / 10000000.0f < CUTDOWN_LATITUDE && \
                  data->gps.longitude_degrees_1000000 / 10000000.0f > CUTDOWN_LONGITUDE && \
                  data->gps.altitude_mm / 1000 > CUTDOWN_ALTITUDE) {
                  system_set_cutdown(CUT_ENABLED);
                  data->rp_cutdown = 1;
              }               
           }    
        #endif          
    } else {
        // Zero out position data if we don't have a valid GPS fix.
        // This is done to avoid transmitting invalid position information.
        data->gps.latitude_degrees_1000000 = 0;
        data->gps.longitude_degrees_1000000 = 0;
        data->gps.altitude_mm = 0;
        data->gps.ground_speed_cm_per_second = 0;
        data->gps.heading_degrees_100000 = 0;
        data->gps.climb_cm_per_second = 0;
    }

#ifdef DFM17
    data->clock_calibration_trim = clock_calibration_get_trim();
    data->clock_calibration_count = clock_calibration_get_change_count();
#endif

// Added RP for temp correction

#ifdef DFM17
    if (RADIO_SI4063_TX_CORRECT == true) {
       t_look = (int) ((data->internal_temperature_celsius_100/100 + 60)/2);
       if (t_look < 0 ){
          t_look = 39;
       }
       if (t_look >49 ){
          t_look = 49;
       }
       data->rp_lu_code = t_look;
       data->rp_xtal_code = c_value[t_look];
    
       si4063_set_crystal_capacitance(data->rp_xtal_code);
    }    

#endif

    locator_from_lonlat(data->gps.longitude_degrees_1000000, data->gps.latitude_degrees_1000000,
            LOCATOR_PAIR_COUNT_FULL, data->locator);

    data->data_counter++;

    log_info("Telemetry collected!\n");
}
