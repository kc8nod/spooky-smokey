#include <SoftwareSerial.h>
#define HAS_SOFTWARE_SERIAL
#include "DYPlayerArduino.h"
#include <Servo.h>
#include "LEDboard.h"
#include "Ghost.h"

/*
 * Arduino pin assignments
 */
#define TRIGGER           A0
#define PLAYER_SERIAL_RX   2
#define PLAYER_SERIAL_TX   3
#define SPI_DATA           4
#define SPI_CLK            5
#define SPI_LATCH          6
#define GHOST_SERVO_LEFT   7
#define GHOST_SERVO_RIGHT  8



const unsigned int IDLE_TIME_INTERVAL = 30000;
unsigned int idle_start_time;

unsigned int show_start_time = 0;
void start_show(){ show_start_time = millis(); }
unsigned int show_elapsed(){ return millis() - show_start_time; }

void wait_until(unsigned int t){
  while(show_elapsed() < t) { 
    update_all();
  }
}
void wait(unsigned int t){
  wait_until(show_elapsed() + t);
}

void show1();
void show2();
void show3();
void show4();
void show_attract();

void (*show_table[])(void) = {
    show1,
    show2,
    show3,
    show4
};

#define SHOW_TABLE_COUNT  (sizeof(show_table) / sizeof(show_table[0]))

SoftwareSerial playerSerialPort(PLAYER_SERIAL_RX, PLAYER_SERIAL_TX);
DY::Player sound(&playerSerialPort);

LEDboard ledBoard = LEDboard(SPI_CLK, SPI_DATA, SPI_LATCH);

Ghost ghost_left(GHOST_SERVO_LEFT);
Ghost ghost_right(GHOST_SERVO_RIGHT);  

void setup() {
  pinMode(TRIGGER, INPUT_PULLUP);
  ledBoard.begin();
  ledBoard.off();
  sound.begin();
  ghost_left.stop();
  ghost_right.stop();

  Serial.begin(9600);
  test();
  Serial.println("Starting!");
  restart_idle_time();
}

void loop() {
  if(digitalRead(TRIGGER) == LOW){
    int showIdx = random(SHOW_TABLE_COUNT);
    Serial.print("start show ");
    Serial.println(showIdx);

    show_table[showIdx]();

    Serial.print("finished show ");
    Serial.println(showIdx);
    restart_idle_time();
  }

test();

  if(idle_time_expired()){
    show_attract();
    restart_idle_time();
  }

}

void restart_idle_time(){ idle_start_time = millis(); }

boolean idle_time_expired(){
    return (millis() - idle_start_time) > IDLE_TIME_INTERVAL;
}

void show1() {
    //   0001
    sound.playSpecified(0);

    // 0-3 no lights
    ledBoard.off();
    wait_until(3000);

    // 3-41.   Fade in to 100% and slow shift between all lights to a visible level % ..
    //  flicker and off
    // Ghosts run full time from 3-41

    // KeyL flicker 27-29 x3
    // Key R flicker 36-38 x3
    
    // Moon pulse

}

void show2() {
    // 0002
    sound.playSpecified(2);

    // 0-4
    // Hill 1 fade in to 75% at 5
    wait_until(2000);
    ledBoard.gate.fade(3000, ledBoard.gate.percent(75));

    // Hill2 fade in to 75 @8
    wait_until(5000);
    ledBoard.hill1.fade(3000, ledBoard.hill1.percent(75));

    // Hill 3 in to 75% @ 11
    wait_until(8000);
    ledBoard.hill2.fade(3000, ledBoard.hill2.percent(75));


    // Moon to full (or phases cycle full)

    // Key lights follow sound of crow calls

    // Ghosts start at 9sec

    // Fade to black all out @40 except crows 

    sound.playSpecified(2);
}

void show3() {
    // 0003

    // Fade moon in to 100 by 4 out by 105

    // Hill 3 fade in 
    // Hill 2 fade in 
    // Hill 1 fade in 
    // Hills all fade by 58

    // Key L @5-12 fast in slow out, @44-51
    // Key R @ 18-26 fast in slow out

    // Ghosts begin @ 22sec

    // Keys flicker @ 58-105 fade flicker
      
    sound.playSpecified(3);

}

void show4() {
    // 0004

    // Moon fade in to full by3sec

    // Ghosts start@0-45 on full time

    // Fade Hill2
    // Fade hill 1
    // Fade hill 3
    // All 3 should pulse in and out randomly

    // Key alternate lighting strikes @ 7,12,22,36,43
    // All fade @44

    sound.playSpecified(4);
}

void show_attract(){
    // 0005
    // All things randomly turn on and off like somethings wrong

    sound.playSpecified(5);
}


void test(){ 
   Serial.println("self test");
   ledBoard.off();

   Serial.println("red");
   ledBoard.moon.set(4095, 0 , 0);
   wait(500);

   Serial.println("green");
   ledBoard.moon.set(0, 4095, 0);
   wait(500);

   Serial.println("blue");
   ledBoard.moon.set(0, 0, 4095);
   wait(500);
   ledBoard.off();

   Serial.println("gate");
   ledBoard.gate.set(4095);
   wait(1000);
   ledBoard.gate.set(0);

   Serial.println("hill1");
   ledBoard.hill1.set(4095);
   wait(1000);
   ledBoard.hill1.set(0);

   Serial.println("hill2");
   ledBoard.hill2.set(4095);
   wait(1000);
   ledBoard.hill2.set(0);

   Serial.println("Key left");
   ledBoard.key_left.set(4095);
   wait(1000);
   ledBoard.key_left.set(0);

   Serial.println("Key right");
   ledBoard.key_right.set(4095);
   wait(1000);
   ledBoard.off();

   Serial.println("sound");
   sound.playSpecified(5);
   
  stop();
}

void stop(){
  Serial.println("stop");
  ledBoard.off();
  sound.stop();
  ghost_left.stop();
  ghost_right.stop();
}

void update_all(){
  ledBoard.update();
  ledBoard.write();
  ghost_left.update();
  ghost_right.update();
}
