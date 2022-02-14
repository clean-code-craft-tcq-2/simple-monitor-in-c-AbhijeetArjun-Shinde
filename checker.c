#include <stdio.h>
#include <assert.h>
#include "checker.h"

BatteryStatus B1 = {0};

void PrintOnConsole(char message[]){
  printf(" %s!\n", message); 
}


int IsThresholdBreached(float parameter, float lowerlimit , float upperlimit){
    if( parameter < lowerlimit )
      return 1;
    else if (parameter > upperlimit) 
      return 2;
    else
      return 0;
    }

int IsInWarningLevel(float parameter, float lowerlimit , float upperlimit){
    if( ( parameter >= lowerlimit) && (parameter <= upperlimit ) )
      return 1;
    else 
      return 0;
    }

int IsNormal(float parameter, float lowerlimit , float upperlimit){
    if( ( parameter > lowerlimit) && (parameter < upperlimit ) )
      return 1;
    else 
      return 0;
    }


BatteryStatus CheckBatteryStatus(BatteryTestData testdata) {

  
  B1.TemperatureStatus.LowBreach = IsThresholdBreached(testdata.Temperature , TemperatureRange.LowerThreshold , TemperatureRange.UpperThreshold );
  B1.TemperatureStatus.LowWarning = IsInWarningLevel(testdata.Temperature ,TemperatureRange.LowerThreshold, TemperatureRange.LowerWarningLimit);
  B1.TemperatureStatus.HighWarning = IsInWarningLevel(testdata.Temperature , TemperatureRange.UpperWarningLimit , TemperatureRange.UpperThreshold);
  B1.TemperatureStatus.HighBreach = IsThresholdBreached(testdata.Temperature , TemperatureRange.LowerThreshold , TemperatureRange.UpperThreshold);
  B1.TemperatureStatus.normal = IsNormal(testdata.Temperature ,TemperatureRange.LowerWarningLimit, TemperatureRange.UpperWarningLimit)  ;
  
  B1.SOCStatus.LowBreach = IsThresholdBreached(testdata.StateOfCharge ,SOCRange);
  B1.SOCStatus.LowWarning = IsInWarningLevel(testdata.StateOfCharge ,SOCRange);
  B1.SOCStatus.HighWarning = IsInWarningLevel(testdata.StateOfCharge ,SOCRange);
  B1.SOCStatus.HighBreach = IsThresholdBreached(testdata.StateOfCharge , SOCRange );
  B1.SOCStatus.normal = IsNormal(testdata.StateOfCharge ,SOCRange.LowerWarningLimit, SOCRange.UpperWarningLimit)  ;
  
  B1.ChargeRateStatus.LowBreach = IsThresholdBreached(testdata.ChargeRate , ChargeRateRange);
  B1.ChargeRateStatus.LowWarning = IsInWarningLevel(testdata.ChargeRate , ChargeRateRange);
  B1.ChargeRateStatus.HighWarning = IsInWarningLevel(testdata.ChargeRate , ChargeRateRange);
  B1.ChargeRateStatus.HighBreach = IsThresholdBreached(testdata.ChargeRate , ChargeRateRange);
  B1.ChargeRateStatus.normal = IsNormal(testdata.ChargeRate ,TemperatureRange.LowerWarningLimit, TemperatureRange.UpperWarningLimit)  ;
  
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
