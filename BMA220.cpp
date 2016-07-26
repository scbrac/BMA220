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
    BMA220_DEBUG_PRINTLN("Try to reset sensor...");
    if (reset() != 0xFF) {
        BMA220_DEBUG_PRINTLN("...failed!");
        return false;
    }
    else {
        BMA220_DEBUG_PRINTLN("...worked!");
        return true;
    }
}

void BMA220::setRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(BMA220_ADDR);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
    }

int8_t BMA220::readRegister(uint8_t reg) {
    BMA220_DEBUG_PRINT("Read register 0x");
    BMA220_DEBUG_PRINTLN_HEX(reg);
    Wire.beginTransmission(BMA220_ADDR);
    BMA220_DEBUG_PRINT("I2C address: 0x");
    BMA220_DEBUG_PRINTLN_HEX(BMA220_ADDR);
    Wire.write(reg);
    BMA220_DEBUG_PRINTLN("Register is selected");
    Wire.endTransmission(); 
    BMA220_DEBUG_PRINTLN("Get one byte...");
    Wire.requestFrom(BMA220_ADDR, ONEBYTE);
    return Wire.read();
}

int8_t BMA220::readAcceleration(uint8_t axis) {
    Wire.beginTransmission(BMA220_ADDR);
    Wire.write(axis);                  // select axis
    Wire.endTransmission(); 
    Wire.requestFrom(BMA220_ADDR, ONEBYTE);
    accdata = Wire.read();       // read acceleration value
    return (int8_t)accdata>>2;   // convert to signed 6 bit value
}

uint8_t BMA220::reset(void) {
    BMA220_DEBUG_PRINTLN("Read reset register");
    resetvalue = readRegister(SOFTRESET_REG);
    BMA220_DEBUG_PRINT("Reset-value: ");
    BMA220_DEBUG_PRINTLN(resetvalue);
    if (resetvalue == 0x00){
        // BMA220 befindet sich im Reset-Modus.
        // Erneutes Lesen beendet den Reset-Modus
        resetvalue = readRegister(SOFTRESET_REG);
        BMA220_DEBUG_PRINT("New reset value: ");
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

