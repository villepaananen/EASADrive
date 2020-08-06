#include <multi_channel_relay.h>
  
Multi_Channel_Relay relay;
const int trigPin = 2;
const int echoPin = 3;

int delayAmount = 500;
long duration;
int distance;

void setup() {
  Serial.begin(9600);
  relay.begin(0x11);

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

  if (distance < 5) {
    flash();
  }

  for (int counter = 0; counter <=7; counter++) {
    if (counter == 0) {
      relay.turn_on_channel(1);
      delay(delayAmount);
    }
    if (counter == 1) {
      relay.turn_off_channel(4);
      delay(delayAmount);
    }
    if (counter == 2) {
      relay.turn_on_channel(2);
      delay(delayAmount);
    }
    if (counter == 3) {
      relay.turn_off_channel(1);
      delay(delayAmount);
    }
    if (counter == 4) {
      relay.turn_on_channel(3);
      delay(delayAmount);
    }
    if (counter == 5) {
      relay.turn_off_channel(2);
      delay(delayAmount);
    }
    if (counter == 6) {
      relay.turn_on_channel(4);
      delay(delayAmount);
    }
    if (counter == 7) {
      relay.turn_off_channel(3);
      delay(delayAmount);
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
