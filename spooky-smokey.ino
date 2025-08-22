
#include "show_functions.h"

#define TRIGGER_PIN A0
#define SERVO_0_PIN 7
#define SERVO_1_PIN 8

const unsigned int IDLE_TIME_INTERVAL = 30000;
unsigned int idle_start_time;



void show_attract(){}

void (*show_table[])(void) = {
    show0,
    show1,
    show2,
    show3
};

#define SHOW_TABLE_COUNT  (sizeof(show_table) / sizeof(show_table[0]))

void setup() {
  pinMode(TRIGGER_PIN, INPUT_PULLUP);

  Serial.begin(9600);
  restart_idle_time();

  Serial.println("Starting!");
}

void loop() {
  if(digitalRead(TRIGGER_PIN) == LOW){
    int showIdx = random(SHOW_TABLE_COUNT);
    Serial.print("start show ");
    Serial.println(showIdx);

    show_table[showIdx]();

    Serial.print("finished show ");
    Serial.println(showIdx);
    restart_idle_time();
  }


  if(idle_time_expired()){
    show_attract();
    restart_idle_time();
  }
}

void restart_idle_time(){ idle_start_time = millis(); }

boolean idle_time_expired(){
    return (millis() - idle_start_time) > IDLE_TIME_INTERVAL;
}

