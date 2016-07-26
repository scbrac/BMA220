/* =========================================================================
 * BMA220 - A library for BMA220 triaxial acceleration sensor
 *
 * This library provides the class BMA220 that uses I2C to communicate
 * with the sensor.
 *
 * License:
 * Copyright (C) 2016 Sönke Carstens-Behrens
 * (carstens-behrens AT rheinahrcampus.de)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses.
 *
   =========================================================================*/

#ifndef BMA220_H
#define BMA220_H

#include "Arduino.h"
#include "Wire.h"

//#define BMA220_DEBUG
#ifdef BMA220_DEBUG
  #define BMA220_DEBUG_PRINT(x) Serial.print(x)
  #define BMA220_DEBUG_PRINTLN(x) Serial.println(x)
  #define BMA220_DEBUG_PRINTLN_HEX(x) Serial.println(x, HEX)
#else
  #define BMA220_DEBUG_PRINT(x)
  #define BMA220_DEBUG_PRINTLN(x)
  #define BMA220_DEBUG_PRINTLN_HEX(x)
#endif

const uint8_t BMA220_ADDR     = 0x0A; // I2C Address of the sensor
const uint8_t XAXIS           = 0x04; // x-axis acceleration value register
const uint8_t YAXIS           = 0x06; // y-axis acceleration value register
const uint8_t ZAXIS           = 0x08; // z-axis acceleration value register
const uint8_t SLOPE_REG       = 0x12; // slope detection parameter
const uint8_t INTRP_MODE_REG  = 0x1A; // interrupt selection
const uint8_t SLEEP_REG       = 0x1E; // sleep enable and duration
const uint8_t SOFTRESET_REG   = 0x32; // softreset (triggered by reading)
const uint8_t SENSITIVITY_REG = 0x22; // sensitivity selection
const uint8_t FILTER_REG      = 0x20; // filter selection
const uint8_t CHIPID_REG      = 0x00; // chip id
const uint8_t REVISIONID_REG  = 0x02; // revision id
const uint8_t INTRP_RES_REG   = 0x1C; // interrupt reset, latch mode
const uint8_t SENS_2g         = 0x00; // Empfindlichkeit: +- 2g
const uint8_t SENS_4g         = 0x01; // Empfindlichkeit: +- 4g
const uint8_t SENS_8g         = 0x02; // Empfindlichkeit: +- 8g
const uint8_t SENS_16g        = 0x03; // Empfindlichkeit: +- 16g
const uint8_t FILTER_32Hz     = 0x05; // cutoff frequency: 32 Hz
const uint8_t FILTER_64Hz     = 0x04; // cutoff frequency: 64 Hz
const uint8_t FILTER_125Hz    = 0x03; // cutoff frequency: 125 Hz
const uint8_t FILTER_250Hz    = 0x02; // cutoff frequency: 250 Hz
const uint8_t FILTER_500Hz    = 0x01; // cutoff frequency: 500 Hz
const uint8_t FILTER_1kHz     = 0x00; // cutoff frequency: 1 kHz
const uint8_t LATCH_0s        = 0x80; // reset interrupt controller, latch time 0s
const uint8_t LATCH_025s      = 0x90; // reset interrupt controller, latch time 0.25s
const uint8_t LATCH_05s       = 0xA0; // reset interrupt controller, latch time 0.5s
const uint8_t LATCH_1s        = 0xB0; // reset interrupt controller, latch time 1s
const uint8_t LATCH_2s        = 0xC0; // reset interrupt controller, latch time 2s
const uint8_t LATCH_4s        = 0xD0; // reset interrupt controller, latch time 4s
const uint8_t LATCH_8s        = 0xE0; // reset interrupt controller, latch time 8s
const uint8_t LATCH_PERM      = 0xF0; // reset interrupt controller, latch permanently
const uint8_t SLEEP_2ms       = 0b01000000; // sleep enabled, 2 ms
const uint8_t SLEEP_10ms      = 0b01001000; // sleep enabled, 10 ms
const uint8_t SLEEP_25ms      = 0b01010000; // sleep enabled, 25 ms
const uint8_t SLEEP_50ms      = 0b01011000; // sleep enabled, 50 ms
const uint8_t SLEEP_100ms     = 0b01100000; // sleep enabled, 100 ms
const uint8_t SLEEP_500ms     = 0b01101000; // sleep enabled, 500 ms
const uint8_t SLEEP_1s        = 0b01110000; // sleep enabled, 1 s
const uint8_t SLEEP_2s        = 0b01111000; // sleep enabled, 2 s
const uint8_t SLOPEDETECT     = 0x38; // select envelope slope detection
const uint8_t SLOPEPAR1       = 0x0D; // slope detection parameter: threshold: 0011, duration: 01
const uint8_t ONEBYTE         = 0x01; // read one byte

class BMA220 {
    public:
        BMA220();
        bool begin(void);
        void setRegister(uint8_t reg, uint8_t value);
        int8_t readRegister(uint8_t reg);
        int8_t readAcceleration(uint8_t axis);
        uint8_t reset(void);
        uint8_t chipID(void);
        uint8_t revisionID(void);

    private:
        uint8_t resetvalue;
        uint8_t accdata;
};
#endif // BMA220_H
