#define TEMP_MIN_LIMIT 0
#define TEMP_MAX_LIMIT 45

#define SOC_MIN_LIMIT 20
#define SOC_MAX_LIMIT 80

#define CHARGERATE_MIN_LIMIT 0.0
#define CHARGERATE_MAX_LIMIT 0.8


typedef struct{
  float Temperature;
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
  int LowBreach;
  int LowWarning;
  int normal;
  int HighWarning;
  int HighBreach;
}ParameterStatus;


typedef struct{
  ParameterStatus TemperatureStatus;
  ParameterStatus SOCStatus;
  ParameterStatus ChargeRateStatus;
}BatteryStatus;


ParameterRange TemperatureRange = {TEMP_MIN_LIMIT , (TEMP_MIN_LIMIT + 0.05 * TEMP_MAX_LIMIT), (TEMP_MAX_LIMIT - 0.05 * TEMP_MAX_LIMIT ) , TEMP_MAX_LIMIT};

ParameterRange SOCRange  = {SOC_MIN_LIMIT, (SOC_MIN_LIMIT + 0.05 * SOC_MAX_LIMIT), (SOC_MAX_LIMIT - 0.05 * SOC_MAX_LIMIT ),SOC_MAX_LIMIT};

ParameterRange ChargeRateRange =  {CHARGERATE_MIN_LIMIT , (CHARGERATE_MIN_LIMIT + 0.05 * CHARGERATE_MAX_LIMIT),(CHARGERATE_MAX_LIMIT - 0.05 * CHARGERATE_MAX_LIMIT ), CHARGERATE_MAX_LIMIT};

void PrintOnConsole( char message[]);

int IsThresholdBreached(float parameter, ParameterRange range);

int IsInLowerWarningLevel(float parameter, ParameterRange range);

int IsInHigherWarningLevel(float parameter, ParameterRange range);

BatteryStatus CheckBatteryStatus(BatteryTestData testdata);

void AssertBatteryIsOk(BatteryStatus result,int expectedresult);
