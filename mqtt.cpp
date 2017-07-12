#include <SPI.h>
#include <UIPEthernet.h>
#include <PubSubClient.h>
#include <avr/wdt.h>

#include "ac.h"

void callback(char* topic, byte* payload, unsigned int length);

byte mac[]    = {  0xFE, 0xED, 0xBA, 0xBE, 0xFA, 0xCE };
byte server[] = { 192, 168, 0, 11 };
byte ip[]     = { 192, 168, 2, 2 };

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);
//PubSubClient client("jack-macpro.local", 1883, callback, ethClient);   // DNS

void callback(char* topic, byte* payload, unsigned int length) {
  if (payload[0] == '0') {
    //analogWrite(5, (payload[1] - 'a') * 9);
    ac_off();
    client.publish("room1/out","OFF");
  }
  if (payload[0] == '1') {
    ac_on();
    client.publish("room1/out","ON");
  }
  wdt_reset();
}

void mqtt_connect() {
  if (client.connect("arduinoClient")) {
    client.publish("room1/out","hello world");
    client.subscribe("room1/in", 1); // QOS 1 - at least once
  }
}

void mqtt_reconnect() {
  if (!client.connected()) {
    mqtt_connect();
  }
}

void mqtt_init() {
  Ethernet.begin(mac);    // DHCP
  delay(1500);
  mqtt_connect();
}
