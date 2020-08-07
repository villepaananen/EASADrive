#include <multi_channel_relay.h>
  
Multi_Channel_Relay relay;
const int trigPin = 2;
const int echoPin = 3;

int delayAmount = 100;
long duration;
int distance;

int counter = 0;

int activationDistance = 30;

void setup() {
  Serial.begin(9600);
  relay.begin(0x11);
  randomSeed(analogRead(0));
  pinMode(trigPin, OUTPUT);
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < activationDistance) {
    // do stuff
    flash();
  } else {
  
    delayAmount = 1000 + random(-30, 30);
  
    switch (counter) {
    case 1:
      relay.turn_on_channel(1);
      delay(delayAmount);
      break;
    case 2:
      relay.turn_off_channel(4);
      delay(delayAmount);
      break;
    case 3:
      relay.turn_on_channel(2);
      delay(delayAmount);
      break;
    case 4:
      relay.turn_off_channel(1);
      delay(delayAmount);
       break;
    case 5:
      relay.turn_on_channel(3);
      delay(delayAmount);
      break;
    case 6:
      relay.turn_off_channel(2);
      delay(delayAmount);
      break;
    case 7:
      relay.turn_on_channel(4);
      delay(delayAmount);
      break;
    case 8:
      relay.turn_off_channel(3);
      delay(delayAmount);
      break;
    }
    
    if (counter == 8) {
      counter = 1;
    } else {
      counter++;
    }
  }
}

void flash() {
  relay.channelCtrl(0x0f);
  delay(200);

  relay.channelCtrl(0x00);
  delay(120);

  relay.channelCtrl(0x0f);
  delay(230);

  relay.channelCtrl(0x00);
  delay(2000);
  
}
