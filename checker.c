#include <stdio.h>
#include <assert.h>
#include "checker.h"

BatteryStatus B1 = {0};

void PrintOnConsole(char message[]){
  printf(" %s!\n", message); 
}


int IsThresholdBreached(float parameter, ParameterRange range){
    if( parameter < range.LowerThreshold || parameter > range.UpperThreshold )
      return 1;
    else 
      return 0;
    }

int IsInLowerWarningLevel(float parameter, ParameterRange range){
    if( ( parameter >= range.LowerThreshold) && (parameter <= range.LowerWarningLimit ) )
      return 1;
    else 
      return 0;
    }

int IsInHigherWarningLevel(float parameter, ParameterRange range){
    if( ( parameter >= range.UpperWarningLimit ) &&  (parameter <= range.UpperThreshold) ) 
      return 1;
    else 
      return 0;
    }

BatteryStatus CheckBatteryStatus(BatteryTestData testdata) {

  
  B1.TemperatureStatus.LowBreach = IsThresholdBreached(testdata.Temperature , TemperatureRange);
  B1.TemperatureStatus.LowWarning = IsInLowerWarningLevel(testdata.Temperature , TemperatureRange);
  B1.TemperatureStatus.HighWarning = IsInHigherWarningLevel(testdata.Temperature , TemperatureRange);
  B1.TemperatureStatus.HighBreach = IsThresholdBreached(testdata.Temperature , TemperatureRange);
  B1.TemperatureStatus.normal = (!B1.TemperatureStatus.LowBreach && !B1.TemperatureStatus.LowWarning && !B1.TemperatureStatus.HighWarning && !B1.TemperatureStatus.HighBreach);
  
  B1.SOCStatus.LowBreach = IsThresholdBreached(testdata.StateOfCharge ,SOCRange);
  B1.SOCStatus.LowWarning = IsInLowerWarningLevel(testdata.StateOfCharge ,SOCRange);
  B1.SOCStatus.HighWarning = IsInHigherWarningLevel(testdata.StateOfCharge ,SOCRange);
  B1.SOCStatus.HighBreach = IsThresholdBreached(testdata.StateOfCharge , SOCRange );
  B1.SOCStatus.normal = (!B1.SOCStatus.LowBreach && !B1.SOCStatus.LowWarning && !B1.SOCStatus.HighWarning && !B1.SOCStatus.HighBreach);
  
  B1.ChargeRateStatus.LowBreach = IsThresholdBreached(testdata.ChargeRate , ChargeRateRange);
  B1.ChargeRateStatus.LowWarning = IsInLowerWarningLevel(testdata.ChargeRate , ChargeRateRange);
  B1.ChargeRateStatus.HighWarning = IsInHigherWarningLevel(testdata.ChargeRate , ChargeRateRange);
  B1.ChargeRateStatus.HighBreach = IsThresholdBreached(testdata.ChargeRate , ChargeRateRange);
  B1.ChargeRateStatus.normal = (!B1.ChargeRateStatus.LowBreach && !B1.ChargeRateStatus.LowWarning && !B1.ChargeRateStatus.HighWarning && !B1.ChargeRateStatus.HighBreach);
  
  return B1;
}

void AssertBatteryIsOk(BatteryStatus result,int expectedresult) {

  assert( (result.TemperatureStatus.normal && result.SOCStatus.normal && result.ChargeRateStatus.normal)  == expectedresult);
}
 
int main() {
  void (*FuncPtrAssertBatteryIsOk)(BatteryStatus , int );
  FuncPtrAssertBatteryIsOk = &AssertBatteryIsOk;
  
  void (*FuncPtrAlertOutOfRange)(char [] );
  FuncPtrAlertOutOfRange = &PrintOnConsole;
  
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
