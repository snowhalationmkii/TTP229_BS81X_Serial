# TTP229_BS81X_Serial

An Arduino IDE based library used for TTP229 & BS81X series touch chips Serial Port (SDO/SCL) reading.\
Compatible with Tontouch TTP229/Holtek BS818/BS814 touch key chips which use serial clock port to send touch key status.\
BS811X I2C library see [this](https://github.com/snowhalationmkii/BS811X_I2C).

## Instruction

<img src="https://p.sda1.dev/22/aaa94cb9a761f70c90ab4fc4ae3c97c8/O1CN01AnqWIH1LdWYaHWUuA2207691322.jpg">\
Above shows the most common touch key modules you can buy online.\
Although the 16 key touch module uses the chip TTP229-BSF.\
<img src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcR8SFdZ7XYakpJYZ0DIo6zCdG3NSy0KVcBx9fMxYE-vLO2ogqLw4mcOgKhcJdRKeygjLlk&usqp=CAU">\
As we can see from the pin definition. TTP229-BSF uses a serial clock port at PIN `12/13`.
Almost all TTP229 types have a `SDO/SCL` port, but it's not a I2C port. It works differently.\
<img src="https://p.sda1.dev/22/5cfb0e0ddc70d1a310f52eeaadad3aab/bs81x.jpg">\
As for BS81X series, they use a similar `data/clock` port to send touch status. In above picture, they are PIN `5/6` (for 814) or `15/16` (for 818) .
Before use this library, you should connect chip serial clock port to Board default I2C port (See table below).
<img src="https://docs.arduino.cc/static/5f90596512320d9577cfa9638fdb6115/a6d36/wiring.png">\
Then you shall open the `examples\TTPBS_read.ino`, Upload it, Check serail port monitor

## Connection

This library is able to work with various Arduino IDE based MCU boards.

| Board  | PIN | Note |
| ------------- |:-------------:|:----------:|
| Arduino Uno     | `A5/A4`     |
| Arduino Mega     | `21/20`     |
| Arduino Leonardo      | `3/2` |
| ESP8266 | `D1/D2` |
| ESP32 | `22/21` |
| Raspberry pi pico | `21/20` | work with mbed-core but earle-core has a first bit issue |

## Method

- `uint16_t readKeys(bool ucs);`\
  Read data from BS811X. Should call before processing data.\
  Return status of 16 keys in bitmap representation. \
  param `ucs` `true|false` use or not use checksum (Only BS81x need)
- `bool checksum();`\
  Calculate checksum and check the status data.\ 
  Return result of this check (Only BS81x need)
- `uint8_t getKey_active();`\
  Return number of first pressed key.\
  return `0` if none key is pressed
- `bool getKey_passive(uint8_t key);`\
  Return true if a key is pressed.\
  param key Number of a key
- `bool getKey_edge(uint8_t direction, uint8_t key) ;`\
  Return true if a edge is detected.\
  param edge direction `1|2` ( rising|falling ), key Number of a key
- `void begin(bool act, uint8_t bitn);`\
  Return true if the initialize process has been a success.\
  param `act` `HIGH|LOW` active-high|low defined by TP1 (See below) for BS81X must be low\
  param `bitn` key number of a chip

## Setting

#### TTP229

TTP229 chip setting is through connecting respective pin to VSS.\
<img src="https://p.sda1.dev/22/fa0a495afb660dad7445e74a1f348606/20250222_215742.jpg">
<img src="https://p.sda1.dev/22/307f74e617e4955522a45d34f2ab8830/ttp229set.jpg">\
As above, if you want to use all 16 keys, you should connect `TP2` to VSS by jumper.\
**As for `TP1`, if you use `active-high` in the method `begin` , you should connect it to VSS by jumper.\
And vice versa, disconnect it from VSS for `active-low`.**

#### BS81X

Only BS818 has option pins. If you want to have your own settings, you may check the table below.
<img src="https://p.sda1.dev/22/662aa5b4d9d3fdc02126509a4ceb0bce/bs818.jpg">\
However, both BS814/BS818 work in `active-low` and don't have an option for active selection.\
**So in the method `begin` you must use `LOW` param or you'll receive wrong data.\
Besides,  `ucs` must be `true` because BS81X use checksum in data.**

## License

Distributed under the [MIT](https://opensource.org/license/mit) License. See LICENSE for more information.

