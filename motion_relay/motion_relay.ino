#include <multi_channel_relay.h>
  
Multi_Channel_Relay relay;

int sensor = 6;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)


void setup() {
  Serial.begin(9600);
  relay.begin(0x11);

  pinMode(sensor, INPUT);    // initialize sensor as an input
}

void loop() {
  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    delay(100);                // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
      sequenceRelays();
    }
  } 
  else {
      delay(200);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }
}

void sequenceRelays() {
  for (int i=1; i<=4; i++) {
    relay.turn_on_channel(i);
    delay(100); 
  
    relay.turn_off_channel(i);
    delay(100);
   }
}
