#include <multi_channel_relay.h>
  
int ledCount = 6;
int ledPins[6] = {3,5,6,9,10,11};
int lightSensorPin = A0;
int maxBrightness = 255;
int dimmingRate = 8;

Multi_Channel_Relay relay;

void setup() {
  Serial.begin(9600);
  relay.begin(0x11);
}

void loop() {
  int lightSensor = analogRead(lightSensorPin);
  int lightSensorNorm = map(lightSensor, 450, 850, 0, 100);
  //Serial.println(lightSensorNorm);

  if (lightSensorNorm < 100) {
    
    relay.turn_on_channel(4);
    delay(100);

    relay.turn_on_channel(3);
    delay(100);

    relay.turn_off_channel(4);
    delay(50);

    relay.turn_on_channel(2);
    delay(100);

    relay.turn_off_channel(3);
    delay(50);

    relay.turn_on_channel(1);
    delay(100);

    relay.turn_off_channel(2);
    delay(50);

    relay.turn_off_channel(1);
    delay(50);



    
    
    Serial.println("Sensor OFF");
    delay(500);
    //echoPins();    
  }
}

void echoPins() {
    for (int i = 0; i < ledCount; i++) {
      for (int counter = 0; counter < 10; counter++) {
        delay(dimmingRate);
        if (counter == 0) {
          analogWrite(ledPins[i], 255);
        }
        if (counter == 8 && i != 5) {
          analogWrite(ledPins[(i+1)%6], 255);
        }
        if (counter == 9) {
          analogWrite(ledPins[i], 0);
        }
    }
  }
}
