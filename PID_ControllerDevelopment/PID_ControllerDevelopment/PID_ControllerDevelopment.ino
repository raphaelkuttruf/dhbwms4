// PID_ControllerDevelopment.ino
// DHBW Mosbach
// Mechatronische Systeme 4
// Dr.-Ing. Vanessa Romero Segovia
// MT17B Gruppe 3 (Sarah Plieninger, Fabian Redaoui, Raphael Kuttruf)

#include "Defines.h" // Check this File before Compiling !
#include "ArduinoIO.h"
#include "Serial_SimulinkInterface.h"
#include "LevelProcess.h"

void setup()
{
  Serial.begin(115200); // start serial connection
}

void loop()
{
  Serial.print(VERSION);
  Serial_SimulinkInterface Interface;
  LevelProcess WaterLevelProcess;
  WaterLevelProcess.SetOperatingFrequency(OPERATING_FREQUENCY);

  // CYCLIC EXECUTION
  while (true)
  {
    WaterLevelProcess.Timer.PrintCycleRuntime_ms();
    Interface.RecieveSerial();
    //Interface.MirrorRecievedSerial();
    Interface.DeserializeControlSample(WaterLevelProcess.Control);

    WaterLevelProcess.Run();

    Interface.SerializeDataSample(WaterLevelProcess.Data);
    Interface.PrintInstanceState();
    Interface.SendSerial();
  }
}

/*
unsigned long runtime = 0;
unsigned long cycletime = 0;
void PrintCycleRuntime()
{
  // Just to see if the wanted operating frequency can be reached
  cycletime = runtime;
  runtime = millis();
  cycletime = runtime - cycletime;
  Serial.print("\n\nCycletime: ");
  Serial.print(cycletime);
  Serial.print(" [ms]\n");
}
*/
