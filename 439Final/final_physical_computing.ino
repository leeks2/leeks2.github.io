// this code draws from the lecture joystick example code

// integers for joystick (pins + x and y value integer)
// x and y joystick read pins
int x = A0;    
int y = A1;
int xval = 0;
int yval = 0;
// button press
bool button = false;
// lives variable to display
int lives = -1;
int testLives = -1;
//buzzer count to activate
int buzzCount = 0;
bool buzzActive = false;
// light count to activate
int lightCount = 0;

void setup() {
  // start serial communication
  Serial.begin(9600);
  // buzzer
  pinMode(11, OUTPUT);
      int i;
  // light
  pinMode(2, OUTPUT);
  // number display
  for(i=3;i<=10;i++) 
      pinMode(i,OUTPUT);
}

void loop() {

  // get xval and yval readings from joystick
  // map from analogread() values to the dimensions of the screen (60 to 200 and 60 to 650)
  xval = map(analogRead(x), 0, 1023, 60, 200);
  yval = map(analogRead(y), 0, 1023, 60, 650);
  // test for button press
  button = digitalRead(13);
  
  //print out x, y and button input from joystick in json readable format
  Serial.print("[");
  Serial.print(xval);
  Serial.print(",");
  Serial.print(yval);
  Serial.print(",");
  Serial.print(button);
  Serial.println("]"); 

  // check if lives (or a laser shoot) is sent over serial
  if (Serial.available() > 0) {   // if there's serial data 
     lives = Serial.read(); // read it
 }

 //display and update lives (test that it didn't get reset to 5 at game beginning or = 10 for a laser)
 if (testLives != lives and lives != 5 and lives != 10){
  // clear display to start, and also set a buzzer timer for when lives change
  clearDisplay();
  buzzCount = 10;
 }
 // display number for each lives count
 if (lives == 5){
    display5();
  }
  else if (lives == 4){
    display4();
  }
  else if (lives == 3){
    display3();
  }
  else if (lives == 2){
    display2();
  }
  else if (lives == 1){
    display1();
  }

  //if all lives lost
  else if (lives == 0){
    clearDisplay();
    // when game is lost, test for first activation of losing buzzer and buzz to show the game is over
    if (not buzzActive){
      buzzCount = 20;
      buzzActive = true;
    }
  }

  // lives = 10 means a laser was shot
  //serial code testing for laser shoot to activate light
  else if (lives == 10){
    // reset lives to testLives so lives still display correctly
    lives = testLives;
    lightCount = 15;
  }
  testLives = lives; 

  //buzz if buzzCount activated
  if (buzzCount > 0){
    buzzCount -= 1;
    analogWrite(11,5);
  }
  // turn off at end of count
  else if (buzzCount == 0){
    analogWrite(11, 0);
    if (lives != 0){
      buzzActive = false;
    }
  }

  // turn on light if lightCount activated
    if (lightCount > 0){
    lightCount -= 1;
    digitalWrite(2, HIGH);
  }
  // turn off at end of count
  else if (lightCount == 0){
    digitalWrite(2, LOW);
  }

  // .01 sec delay
  delay(10);
}


// pin nums for the 1 digit display
int a=6; 
int b=5; 
int c=4; 
int d=10; 
int e=9; 
int f=7; 
int g=8; 
int dp=3; 

//display number 1
void display1(void) 
{ 
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
} 
//display number2
void display2(void) 
{
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(g,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(d,HIGH);
} 
// display number3
void display3(void) 
{ 
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(g,HIGH);
} 
// display number4
void display4(void) 
{ 
    digitalWrite(f,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(g,HIGH);
    digitalWrite(c,HIGH); 
}
 
// display number5
void display5(void) 
{ 
    digitalWrite(a,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
  digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
} 

// set display off
void clearDisplay(void) 
{ 
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);
    digitalWrite(g,LOW);
  digitalWrite(c,LOW);
    digitalWrite(d,LOW);  
    digitalWrite(e,LOW);  
  digitalWrite(f,LOW);  
} 
