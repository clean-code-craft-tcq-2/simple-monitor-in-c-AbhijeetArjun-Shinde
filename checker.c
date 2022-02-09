#include <stdio.h>
#include <assert.h>
#include "checker.h"

void PrintOnConsole( char message[]){
  printf(" %s is out of range!\n", message);
}

int IsParameterInRange(float parameter, float minvalue , float maxvalue, char parametername[]){
    if(parameter < minvalue || parameter > maxvalue) {
      PrintOnConsole(parametername);
      return 0;
    }
  return 1;
}

void AssertBatteryIsOk(BatteryTestData testdata, int expectedresult) {
  int output;
  output = IsParameterInRange(testdata.Temperature , TEMP_MIN_LIMIT , TEMP_MAX_LIMIT, "Temperature");
  output &= IsParameterInRange(testdata.StateOfCharge, SOC_MIN_LIMIT , SOC_MAX_LIMIT, "State of charge" );
  output &= IsParameterInRange(testdata.ChargeRate , CHARGERATE_MIN_LIMIT , CHARGERATE_MAX_LIMIT,"Charhe Rate");
  assert( output == expected result);
}

 
int main() {
  BatteryTestData testdata[5] = { 
    { 20, 70, 0.7},
    { 50, 85, 0},
    { -5, 50, 0.5},
    { 20, 10, 2 },
    { 35, 30, -4}
  };
  AssertBatteryIsOk(testdata[0],1);
  AssertBatteryIsOk(testdata[1],0);
  AssertBatteryIsOk(testdata[2],0);
  AssertBatteryIsOk(testdata[3],0);
  AssertBatteryIsOk(testdata[4],0);
}
