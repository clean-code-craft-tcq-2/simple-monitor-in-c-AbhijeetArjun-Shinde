#include <stdio.h>
#include <assert.h>
#include "checker.h"

void PrintOnConsole( char message[]){
  printf(" %s is out of range!\n", message);
}

int IsParameterInRange(float parameter, float minvalue , float maxvalue){
    if(parameter < minvalue || parameter > maxvalue) {
      return 0;
    }
  return 1;
}

int AssertBatteryIsOk(BatteryTestData testdata) {
  int output;
  output = IsParameterInRange(testdata.Temperature , TEMP_MIN_LIMIT , TEMP_MAX_LIMIT);
  if(!output){
    PrintOnConsole("Temperature");
  }
  output &= IsParameterInRange(testdata.StateOfCharge, SOC_MIN_LIMIT , SOC_MAX_LIMIT );
  if(!output){
    PrintOnConsole("State of Charge");
  }
  output &= IsParameterInRange(testdata.ChargeRate , CHARGERATE_MIN_LIMIT , CHARGERATE_MAX_LIMIT);
   if(!output){
    PrintOnConsole("Charge Rate");
  }
  return (output);
}

 
int main() {
  BatteryTestData testdata[5] = { 
    { 20, 70, 0.7},
    { 50, 85, 0},
    { -5, 50, 0.5},
    { 20, 10, 2 },
    { 35, 30, -4}
  };
  assert(AssertBatteryIsOk(testdata[0]));
  assert(!AssertBatteryIsOk(testdata[1]));
  assert(!AssertBatteryIsOk(testdata[2]));
  assert(!AssertBatteryIsOk(testdata[3]));
  assert(!AssertBatteryIsOk(testdata[4]));
}
