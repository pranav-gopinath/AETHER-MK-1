#define LED 2 // define the LED bulb
void setup() {
pinMode(LED,OUTPUT); //Set the LED pin as output pin
}

void loop() {
digitalWrite(LED,HIGH); // LED bulb on
delay(1000); // delay time
digitalWrite(LED,LOW); // LED off
delay(1000); //delay time
}
