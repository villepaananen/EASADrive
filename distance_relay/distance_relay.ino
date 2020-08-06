#include <multi_channel_relay.h>
  
Multi_Channel_Relay relay;
const int trigPin = 2;
const int echoPin = 3;

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
    for (int i=1; i<=4; i++) {
      relay.turn_on_channel(i);
      delay(100 * i);
    }

    for (int i=1; i<=4; i++) {
      relay.turn_off_channel(i);
      delay(100 * (5-i));
    }

    delay(500);  
  }
}
