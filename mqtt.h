#include <SPI.h>
#include <UIPEthernet.h>
#include <PubSubClient.h>

#include <ac.h>

void mqtt_reconnect();
void mqtt_connect();
void mqtt_init();

extern PubSubClient client;
