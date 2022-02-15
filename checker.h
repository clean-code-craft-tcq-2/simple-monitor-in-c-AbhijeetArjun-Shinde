#include <stdbool.h>
#include <string.h>
#define TEMP_MIN_LIMIT 0
#define TEMP_MAX_LIMIT 45

#define SOC_MIN_LIMIT 20
#define SOC_MAX_LIMIT 80

#define CHARGERATE_MIN_LIMIT 0.0
#define CHARGERATE_MAX_LIMIT 0.8

typedef struct{
  float Temperature;
  char TemperatureUnit;
  float StateOfCharge;
  float ChargeRate;
} BatteryTestData;

typedef struct{
  float LowerThreshold;
  float LowerWarningLimit;
  float UpperWarningLimit;
  float UpperThreshold;
}ParameterRange;

typedef struct{
  // range check result
  bool LowBreach;
  bool LowWarning;
  bool normal;
  bool HighWarning;
  bool HighBreach;
}ParameterStatus;


typedef struct{
  ParameterStatus TemperatureStatus;
  ParameterStatus SOCStatus;
  ParameterStatus ChargeRateStatus;
}BatteryStatus;

char DisplayMessageEn[12][50] = { " Temperature Low Threshold Breached " , " Temperature Approaching Low Threshold Breach" , " Temperature Approaching High Threshold Breach" , " Temperature High Threshold Breached " ,
                                " State of Charge Low Threshold Breached " , " State of Charge Approaching Low Threshold Breach" , " State of Charge Approaching High Threshold Breach" , " State of Charge High Threshold Breached " ,
                               " Charge Rate Low Threshold Breached " , " Charge Rate Approaching Low Threshold Breach" , " Charge Rate Approaching High Threshold Breach" , " Charge Rate High Threshold Breached " };
char DisplayMessageDe[12][50] ={ " Temperatur unterer Schwellenwert überschritten " , " Temperatur nahe unterem Schwellenwert überschritten" , " Temperatur nahe oberem Schwellenwert überschritten" , " Temperatur oberer Schwellenwert überschritten" ,
                                " Zustand der Ladung - Niedriger Schwellenwert verletzt " , " Zustand der Ladung - Annäherung an niedrigen Schwellenwert verletzt" , " Zustand der Ladung - Annäherung an hohen Schwellenwert verletzt" , " Zustand der Ladung - hoher Schwellenwert verletzt" ,
                               " Charge Rate Low Threshold Breached " , " Charge Rate Approaching Low Threshold Breach" , " Charge Rate Approaching High Threshold Breach" , " Charge Rate High Threshold Breached " };

ParameterRange TemperatureRange = {TEMP_MIN_LIMIT , (TEMP_MIN_LIMIT + 0.05 * TEMP_MAX_LIMIT), (TEMP_MAX_LIMIT - 0.05 * TEMP_MAX_LIMIT ) , TEMP_MAX_LIMIT};

ParameterRange SOCRange  = {SOC_MIN_LIMIT, (SOC_MIN_LIMIT + 0.05 * SOC_MAX_LIMIT), (SOC_MAX_LIMIT - 0.05 * SOC_MAX_LIMIT ),SOC_MAX_LIMIT};

ParameterRange ChargeRateRange =  {CHARGERATE_MIN_LIMIT , (CHARGERATE_MIN_LIMIT + 0.05 * CHARGERATE_MAX_LIMIT),(CHARGERATE_MAX_LIMIT - 0.05 * CHARGERATE_MAX_LIMIT ), CHARGERATE_MAX_LIMIT};

void PrintOnConsole(const char *message);

bool IsLowerThresholdBreached(float parameter, float lowerlimit);

bool IsUpperThresholdBreached(float parameter,float upperlimit);

bool IsInWarningLevel(float parameter, float lowerlimit , float upperlimit);

bool IsNormal(float parameter, float lowerlimit , float upperlimit);

bool CheckBatteryStatus(BatteryTestData testdata);

void AssertBatteryIsOk(bool result,int expectedresult);

float ConvertFarenheitToCelcius( float farenheit);

BatteryTestData CheckAndConvertTemperatureUnit( BatteryTestData testdata );

bool CheckBatteryTemperature( float Temperature , ParameterRange TempRange);

bool CheckBatterySOC( float SOC , ParameterRange SOCRange);

bool CheckBatteryChargeRate( float ChargeRate ,ParameterRange ChargeRateRange);

void BreachAlerter( bool status, char parametername[] );
