#include <multi_channel_relay.h>

// relay1 is the top row, relay2 is the bottom row  
Multi_Channel_Relay relay1;
Multi_Channel_Relay relay2;

int trig1Pin = 2;
int echo1Pin = 3;

int trig2Pin = 4;
int echo2Pin = 5;

int delayAmount = 100;
long duration;
int distance;

int counter = 0;
int activationDistance = 30;

int distance1 = 0;
int distance2 = 0;

int speedIncrease = 0;

void setup() {
  Serial.begin(9600);

  relay1.begin(0x21);
  relay2.begin(0x22);

  randomSeed(analogRead(0));
  pinMode(trig1Pin, OUTPUT);
  pinMode(trig2Pin, OUTPUT);
}

void loop() {
  distance1 = readDistance(trig1Pin, echo1Pin);
  distance2 = readDistance(trig2Pin, echo2Pin);

  // Prints the distance on the Serial Monitor
  Serial.print("Distance1: ");
  Serial.println(distance1);

  Serial.print("Distance2: ");
  Serial.println(distance2);

  // How many sensors are activated
  int counts = 0;
  
  if (distance1 < activationDistance && distance1 > 0) {
    counts++;
  }

  if (distance2 < activationDistance && distance2 > 0) {
    counts++;
  }

  if (counts == 1) {
    speedIncrease++;
    flash();
  } 
  else {
    speedIncrease = 0;
    delayAmount = 900 + random(-30, 30) - 700 * counts;
    
    switch (counter) {
    case 1:
      relay1.turn_on_channel(1);
      delay(delayAmount);
      break;
    case 2:
      relay2.turn_on_channel(1);
      delay(delayAmount);
      break;
    case 3:
      relay1.turn_off_channel(4);
      delay(delayAmount);
      break;
    case 4:
      relay2.turn_off_channel(4);
      delay(delayAmount);
       break;
    case 5:
      relay1.turn_on_channel(2);
      delay(delayAmount);
      break;
    case 6:
      relay2.turn_on_channel(2);
      delay(delayAmount);
      break;
    case 7:
      relay1.turn_off_channel(1);
      delay(delayAmount);
      break;
    case 8:
      relay2.turn_off_channel(1);
      delay(delayAmount);
      break;
    case 9:
      relay1.turn_on_channel(3);
      delay(delayAmount);
      break;
    case 10:
      relay2.turn_on_channel(3);
      delay(delayAmount);
      break;
    case 11:
      relay1.turn_off_channel(2);
      delay(delayAmount);
      break;
    case 12:
      relay2.turn_off_channel(2);
      delay(delayAmount);
       break;
    case 13:
      relay1.turn_on_channel(4);
      delay(delayAmount);
      break;
    case 14:
      relay2.turn_on_channel(4);
      delay(delayAmount);
      break;
    case 15:
      relay1.turn_off_channel(3);
      delay(delayAmount);
      break;
    case 16:
      relay2.turn_off_channel(3);
      delay(delayAmount);
      break;
    }    
    
    if (counter == 16) {
      counter = 1;
    } else {
      counter++;
    }
  }
}

void flash() {
  relay1.channelCtrl(0x0f);
  relay2.channelCtrl(0x0f);
  delay(max(1000- 50 * speedIncrease, 200));

  relay1.channelCtrl(0x00);
  relay2.channelCtrl(0x00);
  delay(max(300 - 50 * speedIncrease, 100));
}

int readDistance(int trigPin, int echoPin) {
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
