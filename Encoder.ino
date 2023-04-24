#include <Servo.h>
Servo c;

#define ctrl_in A0
int A = 12;
int B = 11;
int I = 10;

int countTick = 0;
int countIndex = 0;
char precTick = 0;
char precIndex = 0;
char tick = 0;
char tickB = 0;
char index = 0;

int signal = 0;
int stage0 = 120;
int stage1 = 240;
int stage2 = 360;
int stage3 = 480;
int stage4 = 600;

//int multiplier = 20;

int stableValue = 0;

int reefState0 = 0;
int reefState1 = 63;
int reefState2 = reefState1 + 100; //plane
int reefState3 = reefState2 + 50;
int reefState4 = reefState3 + 50;

void setup() {
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(I, INPUT);
  pinMode(ctrl_in, INPUT);
  Serial.begin(9600);
  c.attach(9);
}

void loop() {
  tick = digitalRead(A);
  tickB = digitalRead(B);
  index = digitalRead(I);
  signal = analogRead(ctrl_in);
  //Serial.print("Signal: ");
  //Serial.println(signal);

  if (signal <= stage0) {
    stableValue = reefState0;
  } else if (signal <= stage1) {
    stableValue = reefState1;
  } else if (signal <= stage2) {
    stableValue = reefState2;
  } else if (signal <= stage3) {
    stableValue = reefState3;
  } else if (signal <= stage4) {
    stableValue = reefState4;
  }
  
 
  if(tick != precTick)
  {
    if(tick != tickB)
    {
      countTick = countTick + tick;
      precTick = tick;
    }
    else
    {
      countTick = countTick - tick;
      precTick = tick;
    }
    char tick_message[50];
    sprintf(tick_message, "tick: %i %i %i\n", countTick, tick, tickB);
    Serial.print(tick_message);
  }




    double ratio = ((double)abs(abs(countTick) - stableValue))/50.0;
if (abs(abs(countTick) - stableValue) > 50) {
  ratio = 1;
}
 if (countTick > stableValue) {
    c.writeMicroseconds(500 + 1000 * (1 - ratio));
  } else if (countTick < stableValue) {
    c.writeMicroseconds(2500 - 1000 * (1 - ratio));
  }
  
}
