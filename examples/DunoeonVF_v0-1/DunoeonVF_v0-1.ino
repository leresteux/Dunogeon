
#include "dunogeon.h"
//#include "drivers.h"
DUNOGEON mondonjon;

//DRIVERS mesCapteurs;

 
// Initialize sensor that uses digital pins trigPin and echoPin / initialisation du capteur avec les broches utilisees.


void setup() {
/*
Serial.begin(9600);
mesCapteurs.servoBegin(3);
mesCapteurs.HCSR04Begin(6,7);
Serial.println(mesCapteurs.PIN_TRIG);
Serial.println(mesCapteurs.HCSR04_cm());
mesCapteurs.servoWrite(90);
delay(1000);
Serial.println(mesCapteurs.HCSR04_cm());
mesCapteurs.servoWrite(0);
delay(1000);


monServo.attach(3); 
monServo.writeMicroseconds(544);
Serial.println(deg2Ms(0));
delay(1000);
monServo.writeMicroseconds(1000);
Serial.println(deg2Ms(180));
delay(1000);
monServo.writeMicroseconds(2400);
Serial.println(deg2Ms(90));
delay(1000);
monServo.writeMicroseconds(deg2Ms(0));
Serial.println(dSens.measureDistanceCm());
  // put your setup code here, to run once:
  */
mondonjon.begin();
}

void loop() {

  // put your main code here, to run repeatedly:

}

