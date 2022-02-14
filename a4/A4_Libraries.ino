// library assignment: Change servo behavior with the remote

// This code uses example code from the lecture for servos and the IR sensor and remote

// servo library and infrared sensor remote library
#include <Servo.h>
#include <IRremote.h>

//Specify which protocol(s) should be used for decoding IR signals.
//If no protocol is defined, all protocols are active.
#define DECODE_NEC 1

int IR_RECEIVE_PIN = 3; // set IR sensor pin

Servo myServo;  // create a servo object

// string to record IR remote inputs, and reference if the input changed
String command = "";
String refCommand = "";

// ints and booleans to record the servo behavior
// whether the servo is on
bool on = true;
// whetehr rotation is clockwise/counterclockwise
bool clockwise = true;
// speed from 1-5
int speed = 1;
// integer to record what degree of rotation the servo is at
int degree = 0;

void setup() {
    // begin serial communication
    Serial.begin(115200);

    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver, enable feedback LED, take LED feedback pin from the internal boards definition
    Serial.print(F("Ready to receive IR signals at pin "));
    Serial.println(IR_RECEIVE_PIN);

    myServo.attach(9); // attaches the servo on pin 9 to the servo object
}

void loop() {
    // part 1: record an input command from the IR sensor and remote
    
    /*
     * Check if received data is available and if yes, try to decode it.
     * Decoded result is in the IrReceiver.decodedIRData structure.
     */
    if (IrReceiver.decode()) {

        // We have an unknown protocol, print more info
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            IrReceiver.printIRResultRawFormatted(&Serial, true);
        }
        Serial.println();
        IrReceiver.resume(); // Enable receiving of the next value

       // record which remote command was received, convert to string
      switch (IrReceiver.decodedIRData.command) {
        case 0x45: command = "Power button";
           break;
        case 0x46: command = "Volume +";
           break;
        case 0x15: command = "Volume -";
           break;
        case 0x47: command = "Func/Stop";
           break;
        case 0x44: command = "Rewind";
           break;
        case 0x40: command = "Play";
           break;
        case 0x43: command = "Fast Forward";
           break;
        case 0x09: command = "Up";
           break;
        case 0x07: command = "Down";
           break;
        case 0x19: command = "EQ";
           break;
        case 0x0D: command = "ST/REPT";
           break;
        case 0x16: command = "0";
           break;
        case 0x0C: command = "1";
           break;
        case 0x18: command = "2";
           break;
        case 0x5E: command = "3";
           break;
        case 0x08: command = "4";
           break;
        case 0x1C: command = "5";
           break;
        case 0x5A: command = "6";
           break;
        case 0x42: command = "7";
           break;
        case 0x52: command = "8";
           break;
        case 0x4A: command = "9";
           break;
      } 
      // print out received command to the serial monitor for testing and reference
      Serial.println(command);  

      // if a command is received, evaluate it to update the servo variables
      if (command != refCommand){
        if(command == "Power button"){
          // reverse the on state
          on = not on;
        }
        refCommand = command;
      }

      // set clockwise or counterclockwise
      if (command == "Fast Forward"){
        clockwise = true;
      }
      else if (command == "Rewind"){
        clockwise = false;
      }
      else if (command == "Up"){
        // higher speed
        speed = 4;
      }
      else if (command == "Down"){
        // lower speed
        speed = 1;
      }
      
      //Serial.print("State-Rotate-Speed ");
      //Serial.print(on);
      //Serial.print(clockwise);
      //Serial.println(speed);
    }

      // part 2: Use input command to determine the servo behavior
      // power toggles rotation on/off
      if (on){
        // fast forward or rewind changes rotation direction
        // up and down volume increase rotation speed (1 vs. 4 times as fast)
        if (clockwise){
          degree += speed;
        }
        else{
          degree -= speed;
        }
        // reset degree at the end of rotation cycle
        if (degree < 0){
          degree = 180;
        }
        else if (degree > 180){
          degree = 0;
        }
        // write servo to rotate to that degree
        myServo.write(degree);
        // set update delay for servo to adjust
        delay(50);
      }
}
