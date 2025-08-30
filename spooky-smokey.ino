#include "DYPlayerArduino.h"
#include "LEDboard.h"

/*
 * Arduino pin assignments
 */
#define TRIGGER           A0
#define GHOST_SERVO_LEFT  7
#define GHOST_SERVO_RIGHT 8

#define SPI_DATA  4
#define SPI_CLK   5
#define SPI_LATCH 6

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

DY::Player player();

LEDboard led = LEDboard(SPI_CLK, SPI_DATA, SPI_LATCH);

void setup() {
  pinMode(TRIGGER, INPUT_PULLUP);
  led.begin();

  Serial.begin(9600);


  Serial.println("Starting!");

restart_idle_time();}

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
    // TODO: implement show0 logic
}

void show1() {
    // TODO: implement show1 logic
}

void show2() {
    // TODO: implement show2 logic
}

void show3() {
    // TODO: implement show3 logic
}

void show_attract(){}

void test(){
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
}