// example capacitive sensor code from lecture and https://playground.arduino.cc/Main/CapacitiveSensor/

// average metric for calibrating capacitive touch
int avg = 0;
// counts to keep track of number of touches
int count = 0;
int ref = 0;
// test whether to exit loop if sensor is activated
long test = 0;

//capacitive sensing library
#include <CapacitiveSensor.h>

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 1 megaohm resistor between pins 4 & 2, pin 2 is sensor pin

void setup() {
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   // start serial monitor
   Serial.begin(9600);

   // set up transistor pin for output
   pinMode(9, OUTPUT);

   //set-up min max and average to calibrate the sensor
   int min = 100;
   int max = 0;
   // for loop to record min-max in calibration period
   for (int i = 0; i < 200; i++){
      // get sensor reading
      long total1 =  cs_4_2.capacitiveSensor(30);
      if (total1 > max){
        max = total1;
      }
      if (total1 < min){
        min = total1;
      }
      delay(10);
   }
   // get average of min/max as metric for touch on/off
   avg = (min + max)/2;
   //print out min, max, avg to serial monitor
   Serial.print("Min Max Avg: ");
   Serial.print(min);
   Serial.print(" ");
   Serial.print(max);
   Serial.print(" ");
   Serial.println(avg);
   delay(500);
}

void loop()                    
{
    // get capacitive sensor reading
    long total1 =  cs_4_2.capacitiveSensor(30);

    // while loop to tell when reading is higher than calibrated average (i.e. touch is on)
    while (total1 > avg){
      // count + 1 for each touch
      count = ref + 1;
      // recalculate to tell when touch deactivates
      total1 =  cs_4_2.capacitiveSensor(30);
    }
    
    // update ref if count changed
    if (ref != count){
      ref = count;
      //print count to monitor
      Serial.print("Count: ");
      Serial.println(count);
    }
    
    // light pattern - off on blink fade

    
    if (count%4 == 1){
      // at part 2 of the pattern, light is on (150/255)
      analogWrite(9, 150);
    }  
     
    else if (count%4 == 2){
      // at part 3 of the pattern, light is blinking (50/255)
      analogWrite(9, 50);
      // .05 sec delay between on/off
      delay(50);
      digitalWrite(9, LOW);
      delay(50);
    }
    
    else if (count%4 == 3){
      // at part 4 of the pattern, light is fading
      // for loop to fade up
      for (int i = 0; i <= 150; i++){
        // test if sensor is touched to exit the fade loop
        test =  cs_4_2.capacitiveSensor(30);
        // if not touched
        if (test < avg and count == ref){
          // analogWrite up to 150
          analogWrite(9, i);
          //.005 sec delay
          delay(5);
        }
        // update count if sensor touched during loop
        else{
          count = ref + 1;
        }
      }
      // for loop to fade down
      for (int i = 150; i >= 0; i--){
        // test if sensor is touched to exit the fade loop
        test =  cs_4_2.capacitiveSensor(30);
        // if not touched
        if (test < avg and count == ref){
          // analogWrite up to 150
          analogWrite(9, i);
          //.005 sec delay
          delay(5);
        }
        // update count if sensor touched during loop
        else{
          count = ref + 1;
        }
      }
    }
    
    else{
      // part 1, light off
      digitalWrite(9, LOW);
    }
}
