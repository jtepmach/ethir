/*
  EthIR mqtt IR blaster over ethernet
*/

#include <avr/wdt.h>

#include "mqtt.h"
#include "ac.h"
#include "ds18b20.h"

void test() {
  while (true) {
    ac_off(); delay(3000);
    ac_on();  delay(3000);
  }
}

void setup()
{
  //test();

  //Serial.begin(9600);
  pinMode(3, OUTPUT); digitalWrite(3, LOW);
  pinMode(5, OUTPUT); digitalWrite(5, LOW);
  
  mqtt_init();
  
  //dht_init();
  
  wdt_disable();
  //enable_watchdog();
}


unsigned long timerA;
void loop()
{
  char str[8];

  client.loop();    // ethernet

  if (millis() > timerA) {
    timerA = millis() + 2000;
    
    mqtt_reconnect();

    int raw = get_ds18b20();
    sprintf(str,"T:%d.%d",raw/16, ((raw & 15)*10)/16);
    client.publish("room1/out",str);
  }
}
