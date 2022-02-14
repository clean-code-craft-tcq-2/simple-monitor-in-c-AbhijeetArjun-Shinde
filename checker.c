#include <stdio.h>
#include <assert.h>
#include "checker.h"

void PrintOnConsole( char message[]){
  printf(" %s is out of range!\n", message);
}

bool IsLowerThresholdBreached(float parameter, ParameterRange range){
    if( parameter < range.LowBreachMaxLimit )
      return 1;
    else 
      return 0;
    }

bool IsUpperThresholdBreached(float parameter, ParameterRange range){
    if( parameter > range.HighBreachMinLimit )
      return 1;
    else 
      return 0;
    }

BatteryStatus CheckBatteryStatus(BatteryTestData testdata) {
  BatteryStatus B1;
  
  B1.TemperatureStatus.LowBreach = IsLowerThresholdBreached(testdata.Temperature , TemperatureRange.LowBreachMaxLimit);
  B1.TemperatureStatus.LowWarning = IsParameterInRange(testdata.Temperature , TemperatureRange.LowWarningMinLimit , TemperatureRange.LowWarningMaxLimit);
  B1.TemperatureStatus.normal = IsParameterInRange(testdata.Temperature , TemperatureRange.NormalMinLimit , TemperatureRange.NormalMaxLimit);
  B1.TemperatureStatus.HighWarning = IsParameterInRange(testdata.Temperature , TemperatureRange.HighWarningMinLimit , TemperatureRange.HighWarningMaxLimit);
  B1.TemperatureStatus.HighBreach = IsUpperThresholdBreached(testdata.Temperature , TemperatureRange.HighBreachMinLimit , TemperatureRange.HighBreachMaxLimit);
  
  B1.SOCStatus.LowBreach = IsLowerThresholdBreached(testdata.StateOfCharge ,SOCRange.LowBreachMaxLimit);
  B1.SOCStatus.LowWarning = IsParameterInRange(testdata.StateOfCharge , SOCRange.LowWarningMinLimit , SOCRange.LowWarningMaxLimit);
  B1.SOCStatus.normal = IsParameterInRange(testdata.StateOfCharge , SOCRange.NormalMinLimit , SOCRange.NormalMaxLimit);
  B1.SOCStatus.HighWarning = IsParameterInRange(testdata.StateOfCharge , SOCRange.HighWarningMinLimit , SOCRange.HighWarningMaxLimit);
  B1.SOCStatus.HighBreach = IsUpperThresholdBreached(testdata.StateOfCharge , SOCRange.HighBreachMinLimit , SOCRange.HighBreachMaxLimit);
  
  
  B1.ChargeRateStatus.LowBreach = IsLowerThresholdBreached(testdata.ChargeRate , ChargeRateRange.LowBreachMaxLimit);
  B1.ChargeRateStatus.LowWarning = IsParameterInRange(testdata.ChargeRate , ChargeRateRange.LowWarningMinLimit , ChargeRateRange.LowWarningMaxLimit);
  B1.ChargeRateStatus.normal = IsParameterInRange(testdata.ChargeRate , ChargeRateRange.NormalMinLimit , ChargeRateRange.NormalMaxLimit);
  B1.ChargeRateStatus.HighWarning = IsParameterInRange(testdata.ChargeRate , ChargeRateRange.HighWarningMinLimit , ChargeRateRange.HighWarningMaxLimit);
  B1.ChargeRateStatus.HighBreach = IsUpperThresholdBreached(testdata.ChargeRate , ChargeRateRange.HighBreachMinLimit , ChargeRateRange.HighBreachMaxLimit);
  
  return B1;
}

void AssertBatteryIsOk(BatteryStatus result,int expectedresult) {

  //assert( result == expectedresult);
}
 
int main() {
  void (*FuncPtrAssertBatteryIsOk)(BatteryStatus , int );
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
