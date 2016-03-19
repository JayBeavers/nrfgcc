#include "mbed.h"

DigitalOut greenLED(P0_22);
DigitalOut blueled(P0_23);

int main() {
    while(1) {
        greenLED = 0; // LED is ON
        wait(0.2); // 200 ms
        greenLED = 1; // LED is OFF
        wait(1.0); // 1 sec
        blueled = 0; // LED is ON
        wait(0.2); // 200 ms
        blueled = 1; // LED is OFF
        wait(1.0); // 1 sec
    }
}
