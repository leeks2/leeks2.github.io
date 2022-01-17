/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 11-13 as an output.
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // first part of blink pattern; turn on then off 3 LEDs in sequence
  //for loop from 11 to 13 (pin numbers)
  for (int i = 11; i <= 13; i++){
    digitalWrite(i, HIGH); // turn LED [i] on with HIGH voltage
    delay(200);            // LED is on for .2 seconds
    digitalWrite(i, LOW);  // turn LED [i] off with LOW voltage
  }

  delay (200);             // .2 second delay after first loop

  // second part of blink pattern, all 3 LEDS on then off at the same time
  digitalWrite(11, HIGH)  // turn LED 11 on with HIGH voltage
  digitalWrite(12, HIGH)  // turn LED 12 on with HIGH voltage
  digitalWrite(13, HIGH)  // turn LED 13 on with HIGH voltage
  delay(200);             // lights are on for .2 seconds
  digitalWrite(11, LOW)  // turn LED 11 off with LOW voltage
  digitalWrite(12, LOW)  // turn LED 12 off with LOW voltage
  digitalWrite(13, LOW)  // turn LED 13 off with LOW voltage
  
}
