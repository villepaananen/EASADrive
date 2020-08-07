#include <multi_channel_relay.h>
  
Multi_Channel_Relay relay;
const int trigPin = 2;
const int echoPin = 3;

int delayAmount = 100;
long duration;
int distance;
int distance2; 

int counter = 0;

int activationDistance = 30;

void setup() {
  Serial.begin(9600);
  relay.begin(0x11);
  randomSeed(analogRead(0));
  pinMode(trigPin, OUTPUT);
}

void loop() {
  distance = readDistance();
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < activationDistance) {
    for (int i=1; i<=4; i++) {
      delayAmount = 500 - i * 50 + random(-50, 50);
      relay.turn_on_channel(i);
      delay(delayAmount);
    }

    distance2 = readDistance();
    Serial.print("Distance2: ");
    Serial.println(distance2);

    if (distance2 < activationDistance) {
      fadeUp();
    } else {
      for (int j=4; j>=1; j--) {
        relay.turn_off_channel(j);
        delay(100);
      }
    } 
  }
}

void fadeUp() {
  for (int i=1; i<=4; i++) {
    delayAmount = 300 - i * 50 + random(-50, 50);
    relay.turn_off_channel(i);
    delay(delayAmount);
  }

  for (int i=1; i<=4; i++) {
    delayAmount = 300 - i * 50 + random(-50, 50);
    relay.turn_on_channel(i);
    delay(delayAmount);
  }

}

int readDistance() {
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

  return distance;
}
