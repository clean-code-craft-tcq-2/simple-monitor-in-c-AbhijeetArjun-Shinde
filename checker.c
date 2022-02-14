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

int CheckBatteryStatus(BatteryTestData testdata) {
  int output;
  output = IsParameterInRange(testdata.Temperature , TEMP_MIN_LIMIT , TEMP_MAX_LIMIT, "Temperature");
  output &= IsParameterInRange(testdata.StateOfCharge, SOC_MIN_LIMIT , SOC_MAX_LIMIT, "State of charge" );
  output &= IsParameterInRange(testdata.ChargeRate , CHARGERATE_MIN_LIMIT , CHARGERATE_MAX_LIMIT,"Charge Rate");
  return output;
}

void AssertBatteryIsOk(int result,int expectedresult) {

  assert( result == expectedresult);
}
 
int main() {
  void (*FuncPtrAssertBatteryIsOk)(int , int );
  FuncPtrAssertBatteryIsOk = &AssertBatteryIsOk
  BatteryTestData testdata[5] = { 
    { 20, 70, 0.7},
    { 50, 85, 0},
    { -5, 50, 0.5},
    { 20, 10, 2 },
    { 35, 30, -4}
  };
  FuncPtrAssertBatteryIsOk(CheckBatteryStatus(testdata[0]),1);
  FuncPtrAssertBatteryIsOk(CheckBatteryStatus(testdata[1]),0);
  FuncPtrAssertBatteryIsOk(CheckBatteryStatus(testdata[2]),0);
  FuncPtrAssertBatteryIsOk(CheckBatteryStatus(testdata[3]),0);
  FuncPtrAssertBatteryIsOk(CheckBatteryStatus(testdata[4]),0);
}
