#pragma once

#define VERSION "Version 0.180\n"

// Compilation Plattform Selection
//#################################################################################################
#define IN_ARDUINO_IDE
//#define IN_VISUALSTUDIO
//#################################################################################################
#define OPERATING_FREQUENCY 50 //[Hz]


//#################################################################################################

//https://www.arduino.cc/reference/de/

// Sample Time, minimum 20ms !
// Serial Communication and Program execution introduce LAG !
//#define CYCLE_DELAY_MS 44
//#define CYCLE_TIME_MS 50
// https://www.elektronik-kompendium.de/sites/kom/0212095.htm
// SendAndRecieveBytes*(8+1) / Baud = Transfertime -> In this Project ~5ms without STATE_PRINTs
// program execution Time ~1ms without STATE_PRINTs
//-> Better Solution with ArduinoTimer Class to have dynamic delay -> constant samplingfrequency

//#################################################################################################

// TEST SERIAL COMMUNICATION AND STAND ALONE
//#define OVERWRITE_CONTROLSAMPLE // run without Simulink and Serial Communication
//#define OVERWRITE_DATASAMPLE // only to check if serial communication with Simulink works

//#################################################################################################

#ifdef IN_VISUALSTUDIO
#include <iostream>
#include <string>
double NumericConsoleInput();
double UnsignedNumericConsoleInput();
//#define SIMULATE_FOTD // Discards IO and compute the System response, // Doesn't work, wrong formula
#define UNIT_TEST // Enable UnitTest() Calls in Object Constructors
//#define FORCE_CYCLETIME

// Print increases Program size and compromizes performance
#define STATE_PRINT // Enables Code inside PrintInstanceState() Calls

// Select Individual PrintInstanceState() Calls
#ifdef STATE_PRINT
#define STATE_PRINT_CONTROLSAMPLE // ControlSample from Simulink
#define STATE_PRINT_DATASAMPLE // DataSample to Simulink
//#define STATE_PRINT_IO // ArduinoIO
//#define STATE_PRINT_TIMER // ArduinoTimer
#define STATE_PRINT_IO_RELEVANT // Level Process relevant ArduinoIO only
//#define STATE_PRINT_SERIAL_BUFFERS // Serial Send and Recieve Data Array decimal interpretation
#define STATE_PRINT_PID // PID Controller
#define STATE_PRINT_2O_FILTER // Second Order Filter
#define STATE_PRINT_FOTD // FOTD Process Model

#endif // STATE_PRINT

#endif // IN_VISUALSTUDIO

//#################################################################################################

#ifdef IN_ARDUINO_IDE
#include "hardwareSerial.h"
#include "Arduino.h"

#define FORCE_CYCLETIME

// Print increases Program size and compromizes performance
//#define STATE_PRINT // Enables Code inside PrintInstanceState() Calls
// Select Individual PrintInstanceState() Calls
#ifdef STATE_PRINT
//#define STATE_PRINT_CONTROLSAMPLE // ControlSample from Simulink
//#define STATE_PRINT_DATASAMPLE // DataSample to Simulink
//#define STATE_PRINT_IO // ArduinoIO
//#define STATE_PRINT_TIMER // ArduinoTimer
//#define STATE_PRINT_IO_RELEVANT // Level Process relevant ArduinoIO only
//#define STATE_PRINT_SERIAL_BUFFERS // Serial Send and Recieve Data Array decimal interpretation
#define STATE_PRINT_PID // PID Controller
//#define STATE_PRINT_2O_FILTER // Second Order Filter
#define STATE_PRINT_FOTD // FOTD Process Model
#endif // STATE_PRINT

#endif // IN_ARDUINO_IDE
