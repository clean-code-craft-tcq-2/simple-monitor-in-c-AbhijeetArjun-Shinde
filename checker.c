#include <stdio.h>
#include <assert.h>
#include "checker.h"

void PrintOnConsole( char message[]){
  printf(" %s is out of range!\n", message);
}

bool IsThresholdBreached(float parameter, ParameterRange range){
    if( parameter < range.LowBreachMaxLimit || parameter > range.HighBreachMinLimit )
      return 1;
    else 
      return 0;
    }

bool IsAtWarningLevel(float parameter, ParameterRange range){
    if( ( (parameter >= range.LowBreachMaxLimit) && (parameter <= range.LowWarningMaxLimit )) ||  ( ( parameter >= range.HighWarningMinLimit ) &&  (parameter <= range.HighBreachMinLimit) ) )
      return 1;
    else 
      return 0;
    }

BatteryStatus CheckBatteryStatus(BatteryTestData testdata) {
  BatteryStatus B1 = {0};
  
  B1.TemperatureStatus.LowBreach = IsThresholdBreached(testdata.Temperature , TemperatureRange.LowBreachMaxLimit);
  B1.TemperatureStatus.LowWarning = IsAtWarningLevel(testdata.Temperature , TemperatureRange.LowWarningMinLimit , TemperatureRange.LowWarningMaxLimit);
  B1.TemperatureStatus.HighWarning = IsAtWarningLevel(testdata.Temperature , TemperatureRange.HighWarningMinLimit , TemperatureRange.HighWarningMaxLimit);
  B1.TemperatureStatus.HighBreach = IsThresholdBreached(testdata.Temperature , TemperatureRange.HighBreachMinLimit);
  
  B1.SOCStatus.LowBreach = IsThresholdBreached(testdata.StateOfCharge ,SOCRange.LowBreachMaxLimit);
  B1.SOCStatus.LowWarning = IsAtWarningLevel(testdata.StateOfCharge , SOCRange.LowWarningMinLimit , SOCRange.LowWarningMaxLimit);
  B1.SOCStatus.HighWarning = IsAtWarningLevel(testdata.StateOfCharge , SOCRange.HighWarningMinLimit , SOCRange.HighWarningMaxLimit);
  B1.SOCStatus.HighBreach = IsThresholdBreached(testdata.StateOfCharge , SOCRange.HighBreachMinLimit );
  
  
  B1.ChargeRateStatus.LowBreach = IsThresholdBreached(testdata.ChargeRate , ChargeRateRange.LowBreachMaxLimit);
  B1.ChargeRateStatus.LowWarning = IsAtWarningLevel(testdata.ChargeRate , ChargeRateRange.LowWarningMinLimit , ChargeRateRange.LowWarningMaxLimit);
  B1.ChargeRateStatus.HighWarning = IsAtWarningLevel(testdata.ChargeRate , ChargeRateRange.HighWarningMinLimit , ChargeRateRange.HighWarningMaxLimit);
  B1.ChargeRateStatus.HighBreach = IsThresholdBreached(testdata.ChargeRate , ChargeRateRange.HighBreachMinLimit);
  
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
