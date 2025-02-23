// Example sketch which shows how to use Arduino to read from TTP229/BS81X touch key
// Connect your Arduino to TTP229/BS81X and upload ino
// Open the serial port monitor
// Serial output is in format like "Key status:0000000000000000  Pressed key: 0"
// Connections See README
//
// created by Nitro_Ice
// snowhalation@gmail.com
//////////////////////////////////////////////////////////////////
//
//TTP229
//        TP2 0 16key  mode
//        TP1 0 active high
//            1 active low
//BS81X
//        ucs true
//        act active low
//
/////////////////////////////////////////////////////////////////


#include <TTPBS_Serial.h>
#define keynum 16                        //chip key number

TTPBS_Serial ttp229;

void setup()
{
    ttp229.begin(LOW, keynum);           //HIGH or LOW according to TP1 or chip
    Serial.begin(9600);
}

void loop()
{
    uint16_t keymap = ttp229.readKeys(false);    //ucs for BS81X
    String map;
    for(uint8_t i = 0;i < keynum;i++) {
      uint8_t bit = bitRead(keymap, i);
      if(bit) { map += '1'; }
      else { map += '0'; }
    }

    Serial.print("Key status:");
    Serial.print(map);

    uint8_t key = ttp229.getKey_active();
    Serial.print("  Pressed key: ");
    Serial.println(key);

    if(ttp229.getKey_passive(8)) {
      Serial.println("Key 8 is pressed！");
    }

    if (ttp229.getKey_edge(1, 2)) {
        Serial.println("Key 2 rising edge detected！");
    }
    else if (ttp229.getKey_edge(2, 2)) {
        Serial.println("Key 2 falling edge detected！");
    }

    delay(1000);
}
