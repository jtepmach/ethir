#include <OneWire.h>
OneWire ds(4);

byte addr[9];

int16_t get_ds18b20()
{
  byte data[12];
    
  if (!ds.search(addr)) {
     ds.reset_search();
     delay(250);
     ds.search(addr);  // return true.  do reset_search() if not
  }
  
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);
  
  delay(1000);
  
  ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  for ( int i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }
  
  int16_t raw = (data[1] << 8) | data[0];
  byte cfg = (data[4] & 0x60);

  // at lower res, low bits are undefined, so zero them
  if      (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
  else if (cfg == 0x20) raw = raw & ~3;  // 10 bit res, 187.5 ms
  else if (cfg == 0x40) raw = raw & ~1;  // 11 bit res, 375 ms
                                         // default 12 bit res, 750 ms conv. time
  
  //(float)raw / 16.0;
  return raw;
}

long readInternalTemp() {
  long result;
  // Read temperature sensor against 1.1V reference
  ADMUX = _BV(REFS1) | _BV(REFS0) | _BV(MUX3);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = (result - 125) * 1075;
  return result;
}
