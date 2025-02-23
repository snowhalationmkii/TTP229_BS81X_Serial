// MIT License
// Copyright (c) 2025 Nitro_Ice
// Created by Nitro_Ice<snowhalation@gmail.com>
// 2025/2/23

#if defined(__AVR_ATmega328P__)

    #pragma message "Use Uno"
    #define SCLPin A5
    #define SDOPin A4

#elif defined(__AVR_ATmega2560__)

    #pragma message "Use Mega"
    #define SCLPin 21
    #define SDOPin 20

#elif defined(__AVR_ATmega32U4__)

    #pragma message "Use Leonardo"
    #define SCLPin 3
    #define SDOPin 2

#elif defined(ESP8266)

    #pragma message "Use ESP8266"
    #define SCLPin D1
    #define SDOPin D2

#elif defined(ESP32)

    #pragma message "Use ESP32"
    #define SCLPin 22
    #define SDOPin 21

#elif defined(ARDUINO_ARCH_MBED_RP2040) || defined(ARDUINO_ARCH_RP2040)

    #pragma message "Use RP2040"
    #define SCLPin 21
    #define SDOPin 20
    #include <cstdint>

#else
#error "Undefined Board!"
#endif

#ifndef TTPBS_Serial_H
#define TTPBS_Serial_H

#include <Arduino.h>

class TTPBS_Serial {
    uint16_t _keys = 0;
    uint16_t _prev_state = 0;
    bool state1;
    bool state2;
    uint8_t _length;
    uint8_t _csum;

public:

    //Read data from BS811X. Should call before processing data.
    //Return status of all keys in bitmap representation. 
    //param ucs true|false use or not use checksum (Only BS81x need)
    uint16_t readKeys(bool ucs);
    //Calculate checksum and check the status data. 
    //Return result of this check (Only BS81x need)
    bool checksum();
    // Return number of first pressed key 
    // return 0 if none key is pressed
    uint8_t getKey_active();
    // Return true if a key is pressed
    // param key Number of key
    bool getKey_passive(uint8_t key);
    // Return true if a edge is detected
    // param edge direction/1/2, key Number of key
    bool getKey_edge(uint8_t direction, uint8_t key) ;
    // Return true if the initialize process has been a success.
    //param act HIGH|LOW active-high|low defined by TP1
    //param bitn key number of a chip
    void begin(bool act, uint8_t bitn);
};


#endif //TTPBS_Serial_H
