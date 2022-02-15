#include <stdio.h>
#include <assert.h>
#include "checker.h"


BatteryStatus B1 = {0};

void PrintOnConsole(char message[]){
  printf(" %s!\n", message); 
}


bool IsLowerThresholdBreached(float parameter, float lowerlimit){
    return ( parameter < lowerlimit) ;
}

bool IsUpperThresholdBreached(float parameter,float upperlimit){
    return (parameter > upperlimit);
}

bool IsInWarningLevel(float parameter, float lowerlimit , float upperlimit){
    return (( parameter >= lowerlimit) && (parameter <= upperlimit ));
}

bool IsNormal(float parameter, float lowerlimit , float upperlimit){
    return (( parameter > lowerlimit) && (parameter < upperlimit ));
}


BatteryTestData CheckAndConvertTemperatureUnit( BatteryTestData testdata ){
  if(testdata.TemperatureUnit == 'f' || testdata.TemperatureUnit == 'F'){
    testdata.Temperature = ConvertFarenheitToCelcius(testdata.Temperature);
    testdata.TemperatureUnit = 'C';
  }  
  return (testdata);    
}

BatteryStatus CheckBatteryStatus(BatteryTestData testdata) {
 
  B1.TemperatureStatus.LowBreach = IsLowerThresholdBreached(testdata.Temperature, TemperatureRange.LowerThreshold );
  B1.TemperatureStatus.LowWarning = IsInWarningLevel(testdata.Temperature ,TemperatureRange.LowerThreshold, TemperatureRange.LowerWarningLimit);
  B1.TemperatureStatus.normal = IsNormal(testdata.Temperature ,TemperatureRange.LowerWarningLimit, TemperatureRange.UpperWarningLimit)  ;
  B1.TemperatureStatus.HighWarning = IsInWarningLevel(testdata.Temperature , TemperatureRange.UpperWarningLimit , TemperatureRange.UpperThreshold);
  B1.TemperatureStatus.HighBreach = IsUpperThresholdBreached(testdata.Temperature , TemperatureRange.UpperThreshold);

  
  B1.SOCStatus.LowBreach = IsLowerThresholdBreached(testdata.StateOfCharge , SOCRange.LowerThreshold );
  B1.SOCStatus.LowWarning = IsInWarningLevel(testdata.StateOfCharge ,SOCRange.LowerThreshold, SOCRange.LowerWarningLimit);
  B1.SOCStatus.normal = IsNormal(testdata.StateOfCharge ,SOCRange.LowerWarningLimit, SOCRange.UpperWarningLimit)  ;
  B1.SOCStatus.HighWarning = IsInWarningLevel(testdata.StateOfCharge , SOCRange.UpperWarningLimit , SOCRange.UpperThreshold);
  B1.SOCStatus.HighBreach = IsUpperThresholdBreached(testdata.StateOfCharge, SOCRange.UpperThreshold);

  
  B1.ChargeRateStatus.LowBreach = IsLowerThresholdBreached(testdata.ChargeRate , ChargeRateRange.LowerThreshold );
  B1.ChargeRateStatus.LowWarning = IsInWarningLevel(testdata.ChargeRate ,ChargeRateRange.LowerThreshold, ChargeRateRange.LowerWarningLimit);
  B1.ChargeRateStatus.normal = IsNormal(testdata.ChargeRate ,ChargeRateRange.LowerWarningLimit, ChargeRateRange.UpperWarningLimit)  ;
  B1.ChargeRateStatus.HighWarning = IsInWarningLevel(testdata.ChargeRate , ChargeRateRange.UpperWarningLimit , ChargeRateRange.UpperThreshold);
  B1.ChargeRateStatus.HighBreach = IsUpperThresholdBreached(testdata.ChargeRate, ChargeRateRange.UpperThreshold);

  
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
    { 20, 'c' ,70, 0.7},
    { 50, 'C', 85, 0},
    { 23, 'f', 50, 0.5},
    { 68, 'F', 10, 2 },
    { 35, 'C', 30, -4}
  };
  FuncPtrAssertBatteryIsOk(CheckBatteryStatus(CheckAndConvertTemperatureUnit(testdata[0])),1);
  FuncPtrAssertBatteryIsOk(CheckBatteryStatus(CheckAndConvertTemperatureUnit(testdata[1])),0);
  FuncPtrAssertBatteryIsOk(CheckBatteryStatus(CheckAndConvertTemperatureUnit(testdata[2])),0);
  FuncPtrAssertBatteryIsOk(CheckBatteryStatus(CheckAndConvertTemperatureUnit(testdata[3])),0);
  FuncPtrAssertBatteryIsOk(CheckBatteryStatus(CheckAndConvertTemperatureUnit(testdata[4])),0);
}
