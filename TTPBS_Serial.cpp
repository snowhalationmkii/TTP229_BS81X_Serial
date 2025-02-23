// MIT License
// Copyright (c) 2025 Nitro_Ice
// Created by Nitro_Ice<snowhalation@gmail.com>
// 2025/2/23

#include "TTPBS_Serial.h"

uint16_t TTPBS_Serial::readKeys(bool ucs) 
{
    _prev_state = _keys;
    _keys = 0;
    uint8_t L = _length;
    uint16_t mask = (1 << _length)-1;
    if(ucs) { L <<= 1; }
    pinMode(SCLPin, OUTPUT); 
    digitalWrite(SCLPin, state2);
    pinMode(SDOPin, OUTPUT);
    digitalWrite(SDOPin, state1);
    delayMicroseconds(93);
    digitalWrite(SDOPin, state2);
    delayMicroseconds(10);
    pinMode(SDOPin, INPUT);
    for (uint8_t i = 0; i < L; i++) {
        digitalWrite(SCLPin, state1);
        delayMicroseconds(1);
        digitalWrite(SCLPin, state2);
        _keys |= digitalRead(SDOPin) << i;
    }
    delayMicroseconds(10);
    if(ucs) {
        _csum = 7 & (_keys >> _length);
        _keys = mask ^ (_keys & mask);
        return _keys;
    }
    else {
        if(state2) {
            _keys = mask ^ (_keys & mask);
            return _keys;
        }
        else {
            return _keys;
        }
    }
}

bool TTPBS_Serial::checksum() 
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < _length; i++) {
        if(bitRead(_keys, i)) {
            count++;
        }
    }
    if(_csum == count){
        return true;
    }
    else {
        return false;
    }
}

uint8_t TTPBS_Serial::getKey_active() 
{
    uint8_t i = 0;
    for (uint16_t mask = 0x0001; mask; mask <<= 1) {
        if (mask & _keys) {
            return i+1;
        }
        ++i;
    }
    return 0;
}

bool TTPBS_Serial::getKey_passive(uint8_t key) 
{
    return bitRead(_keys, key-1);
}

bool TTPBS_Serial::getKey_edge(uint8_t direction, uint8_t key) 
{
    if(direction == 1){ return !bitRead(_prev_state, key-1) && bitRead(_keys, key-1); }
    else if (direction == 2) { return bitRead(_prev_state, key-1) && !bitRead(_keys, key-1); }
    else { return false; }
}

void TTPBS_Serial::begin(bool act, uint8_t bitn)
{
    if(act) {
        state1 = HIGH;
        state2 = LOW;
    }
    else {
        state1 = LOW;
        state2 = HIGH;
    }
    _length = bitn;
}
