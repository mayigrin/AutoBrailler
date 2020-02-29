#include <Arduino.h>
#include <string.h>
#include <math.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h> 

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;
Servo motor;

const int ON_ANGLE = 30;
const int OFF_ANGLE = 60;
const int SERVO_MOVEMENT_DELAY = 250;
const int CURRENT_THRESHOLD = 255;
const int CARRIAGE_PULL_FORWARD_TIME = 12000;
const int CARRIAGE_PULL_BACKWARD_TIME = 6000;

void setup() {  
  Serial.begin(9600);
  
  // attach the servos
  servo1.attach(4);
  servo2.attach(3);
  servo3.attach(2);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);
  servo7.attach(8);
  servo8.attach(9);
  motor.attach(10);

  retractServos();
  
}

void loop() {
  //First wait for communication to begin
  bool waiting=true;
  while(waiting) {
    if(Serial.available()>0) {
      if(Serial.read()==5) {
        waiting=false;
      }
    }
    else {
      delay(0.25);
    }
  }

  //Then send the acknowledge signal
  Serial.write(2);

  //Now we wait for the song data to come.
  bool printing=true;

  while(printing) {
    if(Serial.available() > 0){
      char chr = Serial.read();
      convert(chr);
      Serial.write(chr);
    }else{
      delay(0.25);
    }
  }
}


void convert(char chr) { 
  char output[9];

  if (isupper(chr)){
    strcpy(output, "00000100");
    triggerServos(output);
  }

  if (isdigit(chr)){
    strcpy(output, "00111100");
    triggerServos(output);
  }
  
  char new_chr = tolower(chr);
  switch(new_chr) {
    case ' ':
      strcpy(output, "00000010");
      break;
    case '\n':
      strcpy(output, "00000001");
      break;
    case '1':
    case 'a': 
      strcpy(output, "10000000");
      break;
    case '2':
    case 'b':
      strcpy(output, "11000000");
      break;
    case '3':
    case 'c':
      strcpy(output, "10010000");
      break;
    case '4':
    case 'd':
      strcpy(output, "10011000");
      break;
    case '5':
    case 'e':
      strcpy(output, "10001000");
      break;
    case '6':
    case 'f':
      strcpy(output, "11010000");
      break;
    case '7':
    case 'g':
      strcpy(output, "11011000");
      break;
    case '8':
    case 'h':
      strcpy(output, "11001000");
      break;
    case '9':
    case 'i':
      strcpy(output, "01010000");
      break;
    case '0':
    case 'j':
      strcpy(output, "01011000");
      break;
    case 'k':
      strcpy(output, "10100000");
      break;
    case 'l':
      strcpy(output, "11100000");
      break;
    case 'm':
      strcpy(output, "10110000");
      break;
    case 'n':
      strcpy(output, "10111000");
      break;
    case 'o':
      strcpy(output, "10101000");
      break;
    case 'p':
      strcpy(output, "11110000");
      break;
    case 'q':
      strcpy(output, "11111000");
      break;
    case 'r':
      strcpy(output, "11101000");
      break;
    case 's':
      strcpy(output, "01110000");
      break;
    case 't':
      strcpy(output, "01111000");
      break;
    case 'u':
      strcpy(output, "10100100");
      break;
    case 'v':
      strcpy(output, "11100100");
      break;
    case 'w':
      strcpy(output, "01011100");
      break;
    case 'x':
      strcpy(output, "10110100");
      break;
    case 'y':
      strcpy(output, "10111100");
      break;
    case 'z':
      strcpy(output, "10101100");
      break;
    case ',':
      strcpy(output, "01000000");
      break;
    case ';':
      strcpy(output, "01100000");
      break;
    case ':':
      strcpy(output, "01001000");
      break;
    case '.':
      strcpy(output, "01001100");
      break;
    case '!':
      strcpy(output, "01101000");
      break;
    case '?':
      strcpy(output, "01100100");
      break;
    case '\'':
      strcpy(output, "00100000");
      break;
    case '-':
      strcpy(output, "00100100");
      break;
  }
  triggerServos(output);
}

void triggerServos(char on[]) {
  if (on[6] == '1' || on[7] != '1') servo7.write(ON_ANGLE);
  if (on[0] == '1') servo1.write(ON_ANGLE);
  if (on[1] == '1') servo2.write(ON_ANGLE);
  if (on[2] == '1') servo3.write(ON_ANGLE);
  if (on[3] == '1') servo4.write(ON_ANGLE);
  if (on[4] == '1') servo5.write(ON_ANGLE);
  if (on[5] == '1') servo6.write(ON_ANGLE);
  if (on[7] == '1'){ 
    servo8.write(ON_ANGLE);
    
    //Handle carriage pullback
    motor.writeMicroseconds(1000); //forwards
    delay(CARRIAGE_PULL_FORWARD_TIME);
    motor.writeMicroseconds(2000); //backwards
    delay(CARRIAGE_PULL_BACKWARD_TIME);
    motor.writeMicroseconds(1500); //stop
    
  }
  delay(SERVO_MOVEMENT_DELAY);
  retractServos();
}
void retractServos() {
  servo1.write(OFF_ANGLE);
  servo2.write(OFF_ANGLE);
  servo3.write(OFF_ANGLE);
  servo4.write(OFF_ANGLE);
  servo5.write(OFF_ANGLE);
  servo6.write(OFF_ANGLE);
  servo7.write(OFF_ANGLE);
  servo8.write(OFF_ANGLE);
  delay(SERVO_MOVEMENT_DELAY);
}
