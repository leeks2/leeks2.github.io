// this code draws from the lecture joystick example code

// integers for joystick (pins + x and y value integer)
int x = A0;    
int y = A1;
int xval = 0;
int yval = 0;
// pin numbers for RGB led
int red = 9;
int green = 10;
int blue = 11;
String color = "red";

void setup() {
  // start serial communication
  Serial.begin(9600);
  // set up RGB led pins
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {
  // get xval and yval readings from joystick
  // map from analogread() values to the dimensions of the screen (800)
  // x mapping reversed (map from pos 450 to 60) to correct flipped alignment
  xval = map(analogRead(x), 0, 1023, 450, 60);
  yval = map(analogRead(y), 0, 1023, 60, 1150);
  //print out x and y input from joystick in json readable format
  Serial.print("[");
  Serial.print(xval);
  Serial.print(",");
  Serial.print(yval);
  Serial.println("]"); 

  // check if color is sent over serial (red, green, blue)
  if (Serial.available() > 0) {   // if there's serial data 
     color = Serial.readString(); // read it
 }
 // send RGB analog output to make red
 if (color == "red"){
    analogWrite(red, 100);
    analogWrite(green, 5);
    analogWrite(blue, 5);
  }
  // send RGB analog output to make green
  else if (color == "green"){
  analogWrite(red, 5);
  analogWrite(green, 100);
  analogWrite(blue, 5);
  }
  // send RGB analog output to make blue
  else if (color == "blue"){
  analogWrite(red, 5);
  analogWrite(green, 5);
  analogWrite(blue, 100);
  }

  delay(10); 
}
