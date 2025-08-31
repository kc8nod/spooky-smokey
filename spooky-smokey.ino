#include <SoftwareSerial.h>
#define HAS_SOFTWARE_SERIAL
#include "DYPlayerArduino.h"
#include "LEDboard.h"
#include <Servo.h>

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

/* Ghost Constants */
#define GHOST_CLOCKWISE 0
#define GHOST_COUNTERCLOCKWISE 180
#define GHOST_STOP 90

const unsigned int IDLE_TIME_INTERVAL = 30000;
unsigned int idle_start_time;

void show0();
void show1();
void show2();
void show3();
void show_attract();

void (*show_table[])(void) = {
    show0,
    show1,
    show2,
    show3
};
#define SHOW_TABLE_COUNT  (sizeof(show_table) / sizeof(show_table[0]))

SoftwareSerial playerSerialPort(PLAYER_SERIAL_RX, PLAYER_SERIAL_TX);
DY::Player sound(&playerSerialPort);

LEDboard led = LEDboard(SPI_CLK, SPI_DATA, SPI_LATCH);

Servo ghost_left;
Servo ghost_right;  

void setup() {
  pinMode(TRIGGER, INPUT_PULLUP);
  led.begin();
  sound.begin();
  ghost_left.attach(GHOST_SERVO_LEFT);
  ghost_right.attach(GHOST_SERVO_RIGHT);

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

void show0() {
    sound.playSpecified(0);
}

void show1() {
    sound.playSpecified(1);
}

void show2() {
    sound.playSpecified(2);
}

void show3() {
    sound.playSpecified(3);
}

void show_attract(){}

void test(){
  Serial.println("self test");
  led.off();

  Serial.println("red");
  led.set_moon(4095, 0, 0);
  delay(500);

  Serial.println("green");
  led.set_moon(0, 4095, 0);
  delay(500);

  Serial.println("blue");
  led.set_moon(0, 0, 4095);
  delay(500);
  led.off();

  Serial.println("gate");
  led.set_gate(4095);
  delay(1000);
  led.set_gate(0);

  Serial.println("hill1");
  led.set_hill1(4095);
  delay(1000);
  led.set_hill1(0);

  Serial.println("hill2");
  led.set_hill2(4095);
  delay(1000);
  led.set_hill2(0);

  Serial.println("Key left");
  led.set_key_left(4095);
  delay(1000);
  led.set_key_left(0);
  Serial.println("Key right");
  led.set_key_right(4095);
  delay(1000);
  led.off();

  Serial.println("sound");
  sound.playSpecified(5);

  Serial.println("left ghost");
  ghost_left.write(GHOST_CLOCKWISE);
  delay(1000);
  ghost_left.write(GHOST_COUNTERCLOCKWISE); 
  delay(1000);
  ghost_left.write(GHOST_STOP);

  Serial.println("right ghost");
  ghost_right.write(GHOST_CLOCKWISE);
  delay(1000);
  ghost_right.write(GHOST_COUNTERCLOCKWISE);
  delay(1000);
  ghost_right.write(GHOST_STOP);

  stop();
}

void stop(){
  Serial.println("stop");
  led.off();
  sound.stop();
  ghost_left.write(90);
  ghost_right.write(GHOST_STOP);
}