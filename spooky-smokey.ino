#include <SoftwareSerial.h>
#define HAS_SOFTWARE_SERIAL
#include "DYPlayerArduino.h"
#include <Servo.h>
#include "LEDboard.h"
#include "Ghost.h"

/*
 * Arduino pin assignments
 */
#define TRIGGER           A5
#define PLAYER_SERIAL_RX   2
#define PLAYER_SERIAL_TX   3
#define SPI_DATA           4
#define SPI_CLK            5
#define SPI_LATCH          6
#define GHOST_SERVO_LEFT   8
#define GHOST_SERVO_RIGHT  7



const unsigned int IDLE_TIME_INTERVAL = 30000;
unsigned int idle_start_time;

unsigned int show_start_time = 0;
void start_show(){ show_start_time = millis(); }
unsigned int show_elapsed(){ return millis() - show_start_time; }

void wait_until(unsigned int t){
  do {
    update_all();
  } while(show_elapsed() < t);
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

Ghost ghost_left(GHOST_SERVO_LEFT, 98);
Ghost ghost_right(GHOST_SERVO_RIGHT, 90);  

void setup() {
  pinMode(TRIGGER, INPUT_PULLUP);
  ledBoard.begin();
  ledBoard.off();
  sound.begin();
  ghost_left.stop();
  ghost_right.stop();

  Serial.begin(115200);

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

  test2();

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
    ledBoard.gate.fadePercent(5000, 50);
    ledBoard.hill1.fadePercent(5000, 50);
    ledBoard.hill2.fadePercent(5000, 50);
    ledBoard.moon.fade_pct(5000, 50);
    ledBoard.key_left.fadePercent(5000, 50);
    ledBoard.key_right.fadePercent(5000, 50);

    ghost_left.ramp_pct(5000, -66);
    ghost_right.ramp_pct(5000, 66);

    wait(5000);

    ledBoard.gate.fadePercent(5000, 80);
    ledBoard.moon.fade_pct(5000, 80);

    wait(5000);

    ledBoard.hill1.fadePercent(5000, 80);
    ledBoard.hill2.fadePercent(5000, 80);
    ledBoard.gate.fadePercent(5000, 50);
    ledBoard.moon.fade_pct(5000, 50);

    wait(5000);

    ledBoard.key_left.fadePercent(5000, 80);
    ledBoard.gate.fadePercent(5000, 80);
    ledBoard.hill1.fadePercent(5000, 50);
    ledBoard.hill2.fadePercent(5000, 50);

    wait(5000);

    // t=23sec
    ledBoard.key_left.fadePercent(2000, 50);
    ledBoard.key_right.fadePercent(2000, 80);
    ledBoard.gate.fadePercent(2000, 50);

    wait(2000);

    // t=25sec
    ledBoard.gate.fadePercent(5000, 30);
    ledBoard.hill1.fadePercent(5000, 30);
    ledBoard.hill2.fadePercent(5000, 30);
    ledBoard.moon.fade_pct(5000, 30);
    ledBoard.key_left.fadePercent(5000, 30);
    ledBoard.key_right.fadePercent(5000, 30);

    //caw 1 27.6 - 28.1
    wait_until(27600);
    ledBoard.key_left.fade(250, ledBoard.key_left.percent(100));
    wait(250);
    ledBoard.key_left.fade(250, 0);

    //caw 2 28.4 - 29.0
    wait_until(28400);
    ledBoard.key_left.fade(300, ledBoard.key_left.percent(100));
    wait(300);
    ledBoard.key_left.fade(300, 0);

    //caw 3 29.2 - 29.8
    wait_until(29200);
    ledBoard.key_left.fade(400, ledBoard.key_left.percent(100));
    wait(400);
    ledBoard.key_left.fade(400, 0);

    wait_until(30000);
    ledBoard.gate.fade(2000, ledBoard.gate.percent(100));
    wait(2000);


    ledBoard.gate.fade(1000, ledBoard.gate.percent(80));
    ledBoard.hill1.fade(2000, ledBoard.hill1.percent(100));
    wait(2000);

    ledBoard.hill1.fade(1000, ledBoard.hill1.percent(80));
    ledBoard.hill2.fade(2000, ledBoard.hill2.percent(100));
    wait(2000);

    // t=36sec
    ledBoard.hill2.fade(1000, ledBoard.hill2.percent(80));
    ledBoard.key_left.fade(2000, ledBoard.key_left.percent(100));

    //caw 3 36.2 - 36.8
    wait_until(36200);
    ledBoard.key_right.fade(300, ledBoard.key_right.percent(100));
    wait(300);
    ledBoard.key_right.fade(300, 0);

    //caw 3 36.9 - 37.6
    wait_until(36900);
    ledBoard.key_right.fade(350, ledBoard.key_right.percent(100));
    wait(350);
    ledBoard.key_right.fade(350, 0);

    // t=38sec
    wait_until(38000);

    ledBoard.key_left.fade(3000, ledBoard.key_left.percent(0));
    ledBoard.key_right.fade(3000, ledBoard.key_right.percent(0), ledBoard.key_right.percent(100));
    wait(3000);

    // t=41sec
    wait_until(41000);

    ghost_left.ramp_pct(1000, 0);
    ghost_right.ramp_pct(1000, 0);

    // Moon pulse

    ledBoard.moon.fade_pct(2000, 100);
    wait(2000);
    ledBoard.moon.fade_pct(2000, 0);
    wait(2000);
    ledBoard.moon.fade_pct(2000, 100);
    wait(2000);
    ledBoard.moon.fade_pct(2000, 0);
    wait(2000);
    ledBoard.moon.fade_pct(2000, 100);
    wait(2000);
    ledBoard.moon.fade_pct(4000, 0);
    wait(4000);

}

void show2() {
    // 0002
    sound.playSpecified(2);

    // 0-4
    // Hill 1 fade in to 75% at 5
    wait_until(2000);
    ledBoard.gate.fadePercent(3000, 75);

    // Hill2 fade in to 75 @8
    wait_until(5000);
    ledBoard.hill1.fadePercent(3000, 75);

    // Hill 3 in to 75% @ 11
    wait_until(8000);
    ledBoard.hill2.fadePercent(3000, 75);


    // Moon to full (or phases cycle full)
    ledBoard.moon.fade_pct(2000, 100);

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


void test2(){ 
  Serial.println("servo test");
  ledBoard.off();

  for(int s=-10; s<10; s+=1) {
    Serial.print("ghosts speed ");
    Serial.println(s);
    ghost_left.set_pct(s);
    ghost_right.set_pct(s);
    wait(1000);
  }
}
