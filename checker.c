#include <stdio.h>
#include <assert.h>
#include "checker.h"

void PrintOnConsole( char message[]){
  printf(" %s is out of range!\n", message);
}

int TestBatteryTempIsOk(float temperature){
    if(temperature < 0 || temperature > 45) {
      PrintOnConsole("Temperature");
      return 0;
    }
  return 1;
}

int TestBatterySocIsOk(float soc){
    if(soc < 20 || soc > 80) {
      PrintOnConsole("State of Charge");
      return 0;
    }
  return 1;
}

int TestBatteryChargeRateIsOk(float chargeRate){
    if(chargeRate > 0.8) {
      PrintOnConsole("Charge Rate");
      return 0;
    }
  return 1;
}

void AssertBatteryIsOk(float temperature, float soc, float chargeRate) {
  assert(TestBatteryTempIsOk(temperature) ==1);
  assert(TestBatterySocIsOk(soc)==1);
  assert(TestBatteryChargeRateIsOk(chargeRate)==1);
}

 
int main() {
  AssertBatteryIsOk(25, 70, 0.7);
  AssertBatteryIsOk(50, 85, 0);
}
