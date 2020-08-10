#include <multi_channel_relay.h>

// relay1 is the top row, relay2 is the bottom row  
Multi_Channel_Relay relay1;
Multi_Channel_Relay relay2;

void setup() {
  Serial.begin(9600);

  relay1.begin(0x21);
  relay2.begin(0x22);
    
  relay1.turn_on_channel(1);
  relay2.turn_on_channel(2);
}

void loop() {
}
