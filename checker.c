#include <stdio.h>
#include <assert.h>
#include "checker.h"

void PrintOnConsole( char message[]){
  printf(" %s is out of range!\n", message);
}

int TestBatteryTempIsOk(float temperature){
    if(temperature < TEMP_MIN_LIMIT || temperature > TEMP_MAX_LIMIT) {
      PrintOnConsole("Temperature");
      return 0;
    }
  return 1;
}

int TestBatterySocIsOk(float soc){
    if(soc < SOC_MIN_LIMIT || soc > SOC_MAX_LIMIT) {
      PrintOnConsole("State of Charge");
      return 0;
    }
  return 1;
}

int TestBatteryChargeRateIsOk(float chargeRate){
    if(chargeRate < CHARGERATE_MIN_LIMIT || chargeRate > CHARGERATE_MAX_LIMIT) {
      PrintOnConsole("Charge Rate");
      return 0;
    }
  return 1;
}

void AssertBatteryIsOk(BatteryTestData testdata , int result) {
  int output;
  output =  TestBatteryTempIsOk(testdata.Temperature);
  output &= TestBatterySocIsOk(testdata.StateOfCharge);
  output &= TestBatteryChargeRateIsOk(testdata.ChargeRate);
  assert( output == result);
}

 
int main() {
  BatteryTestData testdata[2] = { 
    { 20, 70, 0.7},
    { 50, 85, 0};
  };
  AssertBatteryIsOk(testdata[0],1);
  AssertBatteryIsOk(testdata[1],0);
}
