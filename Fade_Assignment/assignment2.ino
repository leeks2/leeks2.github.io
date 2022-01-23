int R = 9;
int G = 10;
int B = 11;

void setup() {
  for(int i=9;i<13;i++){
    pinMode(i, OUTPUT);
  }
}
void loop() {

  //pink
  for (int i = 0; i <= 50; i++){
  analogWrite(R,i);
  analogWrite(G,0);
  analogWrite(B,i/2);
  delay(50);
  }
  for (int i = 50; i >= 0; i--){
  analogWrite(R,i);
  analogWrite(G,0);
  analogWrite(B,i/2);
  delay(20); 
  }

  //orange
  for (int i = 0; i <= 50; i++){
  analogWrite(R,i);
  analogWrite(G,i/4);
  analogWrite(B,0);
  delay(50);
  }
  for (int i = 50; i >= 0; i--){
  analogWrite(R,i);
  analogWrite(G,i/4);
  analogWrite(B,0);
  delay(20);
  }
}
