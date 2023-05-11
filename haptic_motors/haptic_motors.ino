#include <Wire.h>
#include "Adafruit_DRV2605.h"
#define TCAADDR 0x70

Adafruit_DRV2605 drv1;

uint8_t effect = 52;
// uint8_t port = 0;

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Serial.println("Initial...");

  // // Initial the motor with the least number
  tcaselect(2);
  if (! drv1.begin()) {
    Serial.println("Could not find DRV2605_1");
    while (1) delay(10);
  }
  drv1.selectLibrary(1);
  // I2C trigger by sending 'go' command 
  // default, internal trigger when sending GO command
  drv1.setMode(DRV2605_MODE_INTTRIG); 
}

void haptic_select(int port){
  Serial.print("port #");  Serial.println(port);
  tcaselect(port);
  // set the effect to play
  drv1.setWaveform(0, effect);  // play effect 
  drv1.setWaveform(1, 0);       // end waveform

  // play the effect!
  drv1.go();
  // wait a bit
  delay(1000);

}
void loop() {

  haptic_select(7);
  haptic_select(2);
  haptic_select(5);
  haptic_select(4);

}
