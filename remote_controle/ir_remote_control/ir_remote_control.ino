#include <IRremote.h>

int IRpin = 11;  // pin for the IR sensor
int LedPin = 13; // led pin

IRrecv irrecv(IRpin);
decode_results results;

void setup()
{
 Serial.begin(9600);
 irrecv.enableIRIn(); // Start the receiver
}

void loop() 
{
 if (irrecv.decode(&results)) 
   {
     Serial.println(results.value, DEC);
       if (results.value == 1086313005)  // change according to your IR remote button number
    {
      digitalWrite(LedPin, 0);
    }
    if (results.value == 1086296175)  // change according  to your IR remote button number
    {
      digitalWrite(LedPin, 1);
    }
     irrecv.resume();   // Receive the next value
   }
}     
