#include <BMA220.h>

BMA220 bma;

void setup() {
    Serial.begin(115200);
    if (!bma.begin()) {
        Serial.println(F("No valid BMA220 sensor found, check wiring"));
        while (true)  // stop here, no reason to go on...
            ;
    }
    // Set sensor sensitivity to 4g
    bma.setRegister(SENSITIVITY_REG, SENS_4g);
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
