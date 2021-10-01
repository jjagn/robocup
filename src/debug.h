#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#define initSerial() Serial.begin(115200)
#else
#define debug(x)
#define debugln(x)
#define initSerial()
#endif

#endif