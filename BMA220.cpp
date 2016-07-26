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

#include "BMA220.h"

BMA220::BMA220(){
}

bool BMA220::begin(void) {
    Wire.begin();
    // Check if a sensor is present.
    // Presence is confirmed by reading two different values of the
    // soft reset register. As side effect the sensor is resetted,
    // of course...
    // Reading the soft reset mode changes the the state:
    // if the returned value is 0xFF, the sensor was in reset mode,
    // if the returned value is 0x00, the sensor was in operation mode.
    BMA220_DEBUG_PRINTLN("Try to reset sensor...");
    resetvalue = readRegister(SOFTRESET_REG); // change mode
    BMA220_DEBUG_PRINT("Reset value at beginning: ");
    BMA220_DEBUG_PRINTLN(resetvalue);
    if (resetvalue == 0xFF) {  // was in reset mode, is in operation mode now
        resetvalue = readRegister(SOFTRESET_REG);  // sensor should be in reset mode now
        BMA220_DEBUG_PRINT("Reset value (should be 0x00) is: ");
        BMA220_DEBUG_PRINTLN_HEX(resetvalue);
    }
    if (resetvalue != 0x00) {
        BMA220_DEBUG_PRINTLN("...failed, no valid mode !");
        BMA220_DEBUG_PRINTLN(resetvalue);
        return false;
    }
    // sensor should be in reset mode
    resetvalue = readRegister(SOFTRESET_REG);
    if (resetvalue != 0xFF) {  // sensor was not in reset mode
        BMA220_DEBUG_PRINTLN("...failed (no reset mode found)!");
        BMA220_DEBUG_PRINTLN(resetvalue);
        return false;
    }
    return true;
}

void BMA220::setRegister(uint8_t reg, uint8_t value) {
    BMA220_DEBUG_PRINT("Set register 0x");
    BMA220_DEBUG_PRINTLN_HEX(reg);
    BMA220_DEBUG_PRINT("  Value: 0x");
    BMA220_DEBUG_PRINTLN_HEX(value);
    Wire.beginTransmission(BMA220_ADDR);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
    }

int8_t BMA220::readRegister(uint8_t reg) {
    BMA220_DEBUG_PRINT("Read register 0x");
    BMA220_DEBUG_PRINTLN_HEX(reg);
    Wire.beginTransmission(BMA220_ADDR);
    Wire.write(reg);
    BMA220_DEBUG_PRINTLN("Register is selected");
    Wire.endTransmission(); 
    BMA220_DEBUG_PRINT("Get one byte...");
#ifdef BMA220_DEBUG
    BMA220_DEBUG_PRINT(" got ");
    BMA220_DEBUG_PRINTLN(Wire.requestFrom(BMA220_ADDR, ONEBYTE));
#else
    Wire.requestFrom(BMA220_ADDR, ONEBYTE);
#endif
    return Wire.read();
}

int8_t BMA220::readAcceleration(uint8_t axis) {
    accdata = readRegister(axis);
    return (int8_t)accdata>>2;   // convert to signed 6 bit value
}

uint8_t BMA220::reset(void) {
    BMA220_DEBUG_PRINTLN("Read reset register");
    resetvalue = readRegister(SOFTRESET_REG);
    BMA220_DEBUG_PRINT("Reset-value: ");
    BMA220_DEBUG_PRINTLN(resetvalue);
    if (resetvalue == 0x00){
        // BMA220 is in reset mode now. Reading soft reset register
        // again, brings the sensor back to operation mode.
        resetvalue = readRegister(SOFTRESET_REG);
        BMA220_DEBUG_PRINT("New reset value (should be 0xFF): ");
        BMA220_DEBUG_PRINTLN_HEX(resetvalue);
    }
    return resetvalue;

}

uint8_t BMA220::chipID(void) {
    return readRegister(CHIPID_REG);
}

uint8_t BMA220::revisionID(void) {
    return readRegister(REVISIONID_REG);
}

