======
BMA220
======

BMA220 - A library for BMA220 triaxial acceleration sensor

This library provides the class BMA220 that uses I2C to communicate
with the sensor.

This is a work in progress, not all features are tested yet!

License:
========

Copyright (C) 2016 Sönke Carstens-Behrens
(carstens-behrens AT rheinahrcampus.de)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses.


Installation
============

Place the BMA220 library folder in your ``arduinosketchfolder/libraries/``
folder. If it is your first library, you may need to create the libraries
subfolder first.

Alternatively, install the ZIP version of the library using the Arduino IDE.

Usage
=====
This is a simple example code::

    #include <BMA220.h>

    BMA220 bma;

    void setup() {
        Serial.begin(9600);
        if (!bma.begin()) {
            Serial.println(F("No valid BMA220 sensor found, check wiring"));
            while (true):  // stop here, no reason to go on...
                ;
        }
    }

    void loop() {
        Serial.print("x-axis: ");
        Serial.println(bma.readAcceleration(XAXIS));
        Serial.print("y-axis: ");
        Serial.println(bma.readAcceleration(YAXIS));
        Serial.print("z-axis: ");
        Serial.println(bma.readAcceleration(ZAXIS));
        delay(1000);
    }


The library provides following methods::

    bool begin(void);
    void setregister(uint8_t reg, uint8_t value);
    int8_t readregister(uint8_t reg);
    int8_t readAcceleration(uint8_t axis);
    uint8_t reset(void);
    uint8_t chipID(void);
    uint8_t revisionID(void);


Acceleration
------------
As you can see from the example, the acceleration values are read by::

    int8_t xacc, yacc, zacc
    xacc = bma.readAcceleration(XAXIS);
    yacc = bma.readAcceleration(YAXIS);
    zacc = bma.readAcceleration(ZAXIS);

The acceleration values range from -32 to 31. For a sensitivity of 2g this
corresponds to an acceleration range from -2g to 1.94g. For other sensitivities
the range scales accordingly.

Sensitivity
-----------
To select the sensor sensitivity, you can e.g. add to the setup following line::

    bma.setRegister(SENSITIVITY_REG, SENS_2g);

Possible values for sensitivity are ``SENS_2g``, ``SENS_4g``, ``SENS_8g``, and
``SENS_16g``.


Lowpass Filter
--------------
The cut-off frequency can be set by::

    bma.setRegister(FILTER_REG, FILTER_32Hz);

Possible values for the cut-off frequency are ``FILTER_32Hz``, ``FILTER_64Hz``,
``FILTER_125Hz``, ``FILTER_250Hz``, ``FILTER_500Hz``, and ``FILTER_1kHz``.

Interrupts
----------
Here is an example for activation slope detection::

    bma.setRegister(INTRP_MODE_REG, SLOPEDETECT);
    bma.setRegister(SLOPE_REG, SLOPEPAR1); // threshold 0b0011, duration 0b01
    bma.setRegister(INTRP_RES_REG, LATCH_1s);

Possible values for the latch time are ``LATCH_0s``, ``LATCH_0s``,
``LATCH_025s``, ``LATCH_05s``, ``LATCH_1s``, ``LATCH_2s``, 
``LATCH_4s``, ``LATCH_8s``, and ``LATCH_PERM``. The interrupt reset of
``INTRP_RES_REG`` is set.

Sleep Mode
----------
In order to set the sensor in sleep mode, try::

    bma.setRegister(SLEEP_REG, SLEEP_500ms);

Possible values for sleep time are ``SLEEP_2ms``, ``SLEEP_10ms``,
``SLEEP_25ms``, ``SLEEP_50ms``, ``SLEEP_100ms``, ``SLEEP_500ms``, ``SLEEP_1s``,
and ``SLEEP_2s``.

This feature has not been tested yet as I had no hardware at hand.
