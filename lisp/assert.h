#pragma once

#ifdef ARDUINO
#include <Arduino.h>
#define assert(__e) do { \
                      if (!(__e)) { \
                        Serial.println(); \
                        Serial.print(F(__FILE__)); \
                        Serial.print(":"); \
                        Serial.print(__LINE__, DEC); \
                        Serial.print(" Assertion failed: "); \
                        Serial.println(F(#__e)); \
                        Serial.println("Restart..."); \
                        exit(-1); \
                      } \
                    } while (0)
#else
#include <cassert>
#endif
