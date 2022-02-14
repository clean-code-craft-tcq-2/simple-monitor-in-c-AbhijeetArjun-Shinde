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

bool IsAtLowerWarningLevel(float parameter, ParameterRange range){
    if( ( parameter >= range.LowBreachMaxLimit) && (parameter <= range.LowWarningMaxLimit ) )
      return 1;
    else 
      return 0;
    }

bool IsAtHigherWarningLevel(float parameter, ParameterRange range){
    if( ( parameter >= range.HighWarningMinLimit ) &&  (parameter <= range.HighBreachMinLimit) ) 
      return 1;
    else 
      return 0;
    }

BatteryStatus CheckBatteryStatus(BatteryTestData testdata) {
  BatteryStatus B1 = {0};
  
  B1.TemperatureStatus.LowBreach = IsThresholdBreached(testdata.Temperature , TemperatureRange);
  B1.TemperatureStatus.LowWarning = IsAtLowerWarningLevel(testdata.Temperature , TemperatureRange);
  B1.TemperatureStatus.HighWarning = IsAtHigherWarningLevel(testdata.Temperature , TemperatureRange);
  B1.TemperatureStatus.HighBreach = IsThresholdBreached(testdata.Temperature , TemperatureRange);
  
  B1.SOCStatus.LowBreach = IsThresholdBreached(testdata.StateOfCharge ,SOCRange);
  B1.SOCStatus.LowWarning = IsAtLowerWarningLevel(testdata.StateOfCharge ,SOCRange);
  B1.SOCStatus.HighWarning = IsAtHigherWarningLevel(testdata.StateOfCharge ,SOCRange);
  B1.SOCStatus.HighBreach = IsThresholdBreached(testdata.StateOfCharge , SOCRange );
  
  
  B1.ChargeRateStatus.LowBreach = IsThresholdBreached(testdata.ChargeRate , ChargeRateRange);
  B1.ChargeRateStatus.LowWarning = IsAtLowerWarningLevel(testdata.ChargeRate , ChargeRateRange);
  B1.ChargeRateStatus.HighWarning = IsAtHigherWarningLevel(testdata.ChargeRate , ChargeRateRange);
  B1.ChargeRateStatus.HighBreach = IsThresholdBreached(testdata.ChargeRate , ChargeRateRange);
  
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
