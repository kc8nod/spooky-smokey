#define TRIGGER_PIN 3

const unsigned int IDLE_TIME_INTERVAL = 30000;
unsigned int idle_start_time;

void (*show_table)(void)[] = {
    show0,
    show1,
    show2,
    show3
};

#define SHOW_TABLE_COUNT  (sizeof(show_table) / sizeof(show_table[0]))

void setup() {
  pinmode(TRIGGER_PIN, INPUT_PULLUP);

  Serial.begin();
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

void show0(){}

void show1(){}

void show2(){}

void show3(){}

void show_attract(){}