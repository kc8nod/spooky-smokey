#include "DYPlayerArduino.h"
#include "LEDboard.h"
#include <SoftwareSerial.h>
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

SoftwareSerial::SoftwareSerial PlayerSerialPort(PLAYER_SERIAL_RX, PLAYER_SERIAL_TX);
DY::Player player(&PlayerSerialPort);

LEDboard led = LEDboard(SPI_CLK, SPI_DATA, SPI_LATCH);

Servo ghost_left;
Servo ghost_right;  

void setup() {
  pinMode(TRIGGER, INPUT_PULLUP);
  led.begin();
  player.begin();
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
    player.play(0);
}

void show1() {
    player.play(1);
}

void show2() {
    player.play(2);
}

void show3() {
    player.play(3);
}

void show_attract(){}

void test(){
  Serial.println("self test");
  led.off();
  led.set_front(4095, 0, 0);
  delay(500);
  led.set_middle(4095, 0, 0);
  delay(500);
  led.set_back(4095, 0, 0);
  delay(500);
  led.set_moon(4095, 0, 0);
  delay(500);

  led.set_front(0, 4095, 0);
  delay(500);
  led.set_middle(0, 4095, 0);
  delay(500);
  led.set_back(0, 4095, 0);
  delay(500);
  led.set_moon(0, 4095, 0);
  delay(500);

  led.set_front(0, 0, 4095);
  delay(500);
  led.set_middle(0, 0, 4095);
  delay(500);
  led.set_back(0, 0, 4095);
  delay(500);
  led.set_moon(0, 0, 4095);
  delay(500);

  led.off();

  led.set_key_left(4095);
  delay(1000);
  led.set_key_left(0);
  led.set_key_right(4095);
  delay(1000);
  led.off();

  player.play(5);

  ghost_left.write(GHOST_CLOCKWISE);
  delay(1000);
  ghost_left.write(GHOST_COUNTERCLOCKWISE); 
  delay(1000);
  ghost_left.write(GHOST_STOP);
  ghost_right.write(GHOST_CLOCKWISE);
  delay(1000);
  ghost_right.write(GHOST_COUNTERCLOCKWISE);
  delay(1000);
  ghost_right.write(GHOST_STOP);
}

void stop(){
  Serial.println("stop");
  led.off();
  player.stop();
  ghost_left.write(0)
}