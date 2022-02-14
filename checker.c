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

BatteryStatus CheckBatteryStatus(BatteryTestData testdata) {
  
  BatteryStatus.TemperatureStatus.LowBreach = IsParameterInRange(testdata.Temperature , TemperatureRange.LowBreachMinLimit , TemperatureRange.LowBreachMaxLimit);
  BatteryStatus.TemperatureStatus.LowWarning = IsParameterInRange(testdata.Temperature , TemperatureRange.LowWarningMinLimit , TemperatureRange.LowWarningMaxLimit);
  BatteryStatus.TemperatureStatus.normal = IsParameterInRange(testdata.Temperature , TemperatureRange.NormalMinLimit , TemperatureRange.NormalMaxLimit);
  BatteryStatus.TemperatureStatus.HighWarning = IsParameterInRange(testdata.Temperature , TemperatureRange.HighWarningMinLimit , TemperatureRange.HighWarningMaxLimit);
  BatteryStatus.TemperatureStatus.HighBreach = IsParameterInRange(testdata.Temperature , TemperatureRange.HighBreachMinLimit , TemperatureRange.HighBreachMaxLimit);
  
  BatteryStatus.SOCStatus.LowBreach = IsParameterInRange(testdata.StateOfCharge , SOCRange.LowBreachMinLimit , SOCRange.LowBreachMaxLimit);
  BatteryStatus.SOCStatus.LowWarning = IsParameterInRange(testdata.StateOfCharge , SOCRange.LowWarningMinLimit , SOCRange.LowWarningMaxLimit);
  BatteryStatus.SOCStatus.normal = IsParameterInRange(testdata.StateOfCharge , SOCRange.NormalMinLimit , SOCRange.NormalMaxLimit);
  BatteryStatus.SOCStatus.HighWarning = IsParameterInRange(testdata.StateOfCharge , SOCRange.HighWarningMinLimit , SOCRange.HighWarningMaxLimit);
  BatteryStatus.SOCStatus.HighBreach = IsParameterInRange(testdata.StateOfCharge , SOCRange.HighBreachMinLimit , SOCRange.HighBreachMaxLimit);
  
  
  BatteryStatus.ChargeRateStatus.LowBreach = IsParameterInRange(testdata.ChargeRate , ChargeRateRange.LowBreachMinLimit , ChargeRateRange.LowBreachMaxLimit);
  BatteryStatus.ChargeRateStatus.LowWarning = IsParameterInRange(testdata.ChargeRate , ChargeRateRange.LowWarningMinLimit , ChargeRateRange.LowWarningMaxLimit);
  BatteryStatus.ChargeRateStatus.normal = IsParameterInRange(testdata.ChargeRate , ChargeRateRange.NormalMinLimit , ChargeRateRange.NormalMaxLimit);
  BatteryStatus.ChargeRateStatus.HighWarning = IsParameterInRange(testdata.ChargeRate , ChargeRateRange.HighWarningMinLimit , ChargeRateRange.HighWarningMaxLimit);
  BatteryStatus.ChargeRateStatus.HighBreach = IsParameterInRange(testdata.ChargeRate , ChargeRateRange.HighBreachMinLimit , ChargeRateRange.HighBreachMaxLimit);
  
  return BatteryStatus;
}

void AssertBatteryIsOk(int result,int expectedresult) {

  assert( result == expectedresult);
}
 
int main() {
  void (*FuncPtrAssertBatteryIsOk)(int , int );
  FuncPtrAssertBatteryIsOk = &AssertBatteryIsOk;
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
