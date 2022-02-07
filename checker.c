#include <stdio.h>
#include <assert.h>

void PrintOnConsole( const char *message){
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

int batteryIsOk(float temperature, float soc, float chargeRate) {
  int BatteryTempOk = TestBatteryTempIsOk(temperature);
  int BatterySocOk = TestBatterySocIsOk(soc);
  int BatteryChargeRateOk = TestBatteryChargeRateIsOk(chargeRate);
  return (BatteryTempOk && BatterySocOk && BatteryChargeRateOk);
}

int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
