#include <stdio.h>
#include <assert.h>
#include "checker.h"


BatteryStatus B1 = {0};

void PrintOnConsole(const char *message){
  printf(" %s!\n", message); 
  return;
}

void BreachAlerter( bool status,int messageID){
  if(status){
    if( DISPLAY_MESSAGE_LANG_ID ==1)
    PrintOnConsole(DisplayMessageEn[messageID]);
    else if( DISPLAY_MESSAGE_LANG_ID ==2)
    PrintOnConsole(DisplayMessageDe[messageID]);
  } 
  return;
}


bool IsLowerThresholdBreached(float parameter, float lowerlimit){
    return( parameter < lowerlimit); 
}

bool IsUpperThresholdBreached(float parameter,float upperlimit){
    return(parameter > upperlimit);
}

bool IsInWarningLevel(float parameter, float lowerlimit , float upperlimit){
    return(( parameter >= lowerlimit) && (parameter <= upperlimit ));
}

bool IsNormal(float parameter, float lowerlimit , float upperlimit){
    return(( parameter > lowerlimit) && (parameter < upperlimit ));
}

float ConvertFarenheitToCelcius(float farenheit){
  return ((farenheit - 32) * 5 / 9);
}

BatteryTestData CheckAndConvertTemperatureUnit( BatteryTestData testdata ){
  if(testdata.TemperatureUnit == 'f' || testdata.TemperatureUnit == 'F'){
    testdata.Temperature = ConvertFarenheitToCelcius(testdata.Temperature);
    testdata.TemperatureUnit = 'C';
  }  
  return (testdata);    
}

bool CheckBatteryTemperature( float Temperature , ParameterRange TempRange){
  B1.TemperatureStatus.LowBreach = IsLowerThresholdBreached(Temperature, TempRange.LowerThreshold);
  B1.TemperatureStatus.LowWarning = IsInWarningLevel(Temperature ,TempRange.LowerThreshold, TempRange.LowerWarningLimit );
  B1.TemperatureStatus.normal = IsNormal(Temperature ,TempRange.LowerWarningLimit, TempRange.UpperWarningLimit)  ;
  B1.TemperatureStatus.HighWarning = IsInWarningLevel(Temperature , TempRange.UpperWarningLimit , TempRange.UpperThreshold );
  B1.TemperatureStatus.HighBreach = IsUpperThresholdBreached(Temperature , TempRange.UpperThreshold );
  if(!B1.TemperatureStatus.normal){
    BreachAlerter(B1.TemperatureStatus.LowBreach,0);
    BreachAlerter(B1.TemperatureStatus.LowWarning,1);
    BreachAlerter(B1.TemperatureStatus.HighWarning,2);
    BreachAlerter(B1.TemperatureStatus.HighBreach,3);
  }
  return (B1.TemperatureStatus.normal); 
}

bool CheckBatterySOC( float SOC , ParameterRange SOCRange){
  B1.SOCStatus.LowBreach = IsLowerThresholdBreached(SOC , SOCRange.LowerThreshold );
  B1.SOCStatus.LowWarning = IsInWarningLevel(SOC,SOCRange.LowerThreshold, SOCRange.LowerWarningLimit);
  B1.SOCStatus.normal = IsNormal(SOC ,SOCRange.LowerWarningLimit, SOCRange.UpperWarningLimit)  ;
  B1.SOCStatus.HighWarning = IsInWarningLevel(SOC , SOCRange.UpperWarningLimit , SOCRange.UpperThreshold);
  B1.SOCStatus.HighBreach = IsUpperThresholdBreached(SOC, SOCRange.UpperThreshold);
  if(!B1.SOCStatus.normal){
    BreachAlerter(B1.SOCStatus.LowBreach,4);
    BreachAlerter(B1.SOCStatus.LowWarning,5);
    BreachAlerter(B1.SOCStatus.HighWarning,6); 
    BreachAlerter(B1.SOCStatus.HighBreach,7);
  }
  return (B1.SOCStatus.normal);
}

bool CheckBatteryChargeRate( float ChargeRate ,ParameterRange ChargeRateRange) {
  B1.ChargeRateStatus.LowBreach = IsLowerThresholdBreached(ChargeRate , ChargeRateRange.LowerThreshold );
  B1.ChargeRateStatus.LowWarning = IsInWarningLevel(ChargeRate ,ChargeRateRange.LowerThreshold, ChargeRateRange.LowerWarningLimit);
  B1.ChargeRateStatus.normal = IsNormal(ChargeRate ,ChargeRateRange.LowerWarningLimit, ChargeRateRange.UpperWarningLimit)  ;
  B1.ChargeRateStatus.HighWarning = IsInWarningLevel(ChargeRate , ChargeRateRange.UpperWarningLimit , ChargeRateRange.UpperThreshold);
  B1.ChargeRateStatus.HighBreach = IsUpperThresholdBreached(ChargeRate, ChargeRateRange.UpperThreshold);
  if(!B1.ChargeRateStatus.normal){
    BreachAlerter(B1.ChargeRateStatus.LowBreach,8);
    BreachAlerter(B1.ChargeRateStatus.LowWarning,9);
    BreachAlerter(B1.ChargeRateStatus.HighWarning,10);
    BreachAlerter(B1.ChargeRateStatus.HighBreach,11);
   }
  return (B1.ChargeRateStatus.normal);
}

bool CheckBatteryStatus(BatteryTestData testdata) {
  bool result=0;
  
  result  = CheckBatteryTemperature( testdata.Temperature , TemperatureRange );
  result &= CheckBatterySOC(testdata.StateOfCharge , SOCRange);
  result &= CheckBatteryChargeRate(testdata.ChargeRate, ChargeRateRange);
  
  return result;
}

void AssertBatteryIsOk(bool result,int expectedresult) {
  assert( result == expectedresult);
}
 
int main() {
  void (*FuncPtrAssertBatteryIsOk)(bool , int );
  FuncPtrAssertBatteryIsOk = &AssertBatteryIsOk;
  
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
