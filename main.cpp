/*
################################################################################
## BY: K-taS
## PROJECT NAME : MelodiStack
## PROJECT MADE WITH: M5Stack, M5Unified and M5Stack-Avatar
## V: 1.0.0
################################################################################
*/
#include <M5Unified.h>
#include <Avatar.h>
float value1 = 0;
float voltage1 = 0;
const int CH1_PIN = 35;
const float MAX_VOLTAGE = 3.3;
const float ANALOG_MAX = 4095;
#define GPIO_PIN 25

uint32_t beep_last_time = 0;
uint8_t beep_volume = 10;
uint32_t beep_total_time = 0;

using namespace m5avatar;

Avatar avatar;

void setup(){
  Serial.begin(115200);
  beep_total_time = millis();
  M5.begin();
  avatar.init();
}

float mouse_size=0;
int sumval = 0;
int queue0=0;
int queue1=0;
int queue2=0;
int queue3=0;
int queue4=0;
int queue5=0;
int queue6=0;
int queue7=0;
int queue8=0;
int queue9=0;

int queue(int input){
    int tmp=queue9;
    queue9=queue8;
    queue8=queue7;
    queue7=queue6;
    queue6=queue5;
    queue5=queue4;
    queue4=queue3;
    queue3=queue2;
    queue2=queue1;
    queue1=queue0;
    queue0=input;
    return tmp;
}


void loop(){
  value1 = analogRead(CH1_PIN);
  sumval+=value1;
  sumval-=queue(value1);

  avatar.setMouthOpenRatio(mouse_size);
  if(value1 != 0.0){
    mouse_size=1.0;
    avatar.setMouthOpenRatio(mouse_size);
    dacWrite(GPIO_PIN, 0);
    delayMicroseconds(int((5000-sumval/10)/1.5));
    dacWrite(GPIO_PIN, beep_volume);
    delayMicroseconds(int((5000-sumval/10)/1.5)
    );
  }

  mouse_size=0;
  M5.update();
}
