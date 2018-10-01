#pragma once

#ifdef ARDUINO
#include <Arduino.h>
#define __printf(__e...) Serial.printf(__e)
#else
#include <cstdio>
#define __printf(__e...) printf(__e)
#endif
