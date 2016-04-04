#include <Wire.h>
#include "I2Cdev.h"
#include <ADXL345.h>
#include <SimbleeForMobile.h>
ADXL345 pAccel;
int16_t bufx = 0;
int16_t bufy = 0;
int16_t bufz = 0;
uint8_t t = 0; 
uint8_t x,y,z;
void setup() {
   Wire.begin();
  // put your setup code here, to run once:
   SimbleeForMobile.advertisementData = "ImuTest";
   SimbleeForMobile.domain = "humanconditionglobal.com";
   SimbleeForMobile.begin();
   pAccel.initialize();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!(millis()%10)){ 
    pAccel.getAcceleration(&bufx, &bufy, &bufz); 
     if (SimbleeForMobile.updatable){
    SimbleeForMobile.updateValue(x, bufx);
    SimbleeForMobile.updateValue(y, bufy);
    SimbleeForMobile.updateValue(z, bufz);
    SimbleeForMobile.updateValue(t, millis()/1000);
  }
  SimbleeForMobile.process();
  }
  
 
  
}

void ui(){
  SimbleeForMobile.beginScreen(WHITE);
  x = SimbleeForMobile.drawText(60, 90, bufx);
  y = SimbleeForMobile.drawText(60, 120, bufy);
  z = SimbleeForMobile.drawText(60, 170, bufz);
  t = SimbleeForMobile.drawText(60, 220, bufz);
  SimbleeForMobile.endScreen();
}

