//#include <DHT.h>
//DHT dht;

/*
#include <dht11.h>
#define DHT11PIN 4
dht11 DHT11;
*/

void dht_read()
{
    //sprintf(str,"T:%d.%d",raw/16, ((raw & 15)*10)/16);
    //client.publish("room1/out",str);
    
    //sprintf(str,"I:%d",readInternalTemp()/1000);
    //client.publish("room1/out",str);
    
    /* DHT Library
    sprintf(str,"H:%04d",dht.getHumidity());
    client.publish("room1/out",str);
    sprintf(str,"T:%02d",(int)dht.getTemperature());
    client.publish("room1/out",str);
    */
    
    /*
    switch (DHT11.read(DHT11PIN)) {
	case DHTLIB_OK:
            sprintf(str,"H:%02d",DHT11.humidity);
            client.publish("room1/out",str);
	    sprintf(str,"T:%02d",DHT11.temperature);
            client.publish("room1/out",str);
	    break;
	case DHTLIB_ERROR_CHECKSUM: 
	  break;
	case DHTLIB_ERROR_TIMEOUT: 
	  break;
	default: 
	  break;
    }
  }
    */
}

void dht_init()
{
  //DHT   dht.setup(4, DHT::DHT11);
}
