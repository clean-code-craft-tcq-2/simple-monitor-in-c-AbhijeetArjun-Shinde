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
  // Range limits
  float LowBreachMinLimit;
  float LowBreachMaxLimit;
  float LowWarningMinLimit;
  float LowWarningMaxLimit;
  float NormalMinLimit;
  float NormalMaxLimit;
  float HighWarningMinLimit;
  float HighWarningMaxLimit;
  float HighBreachMinLimit;
  float HighBreachMaxLimit;
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


ParameterRange TemperatureRange = {0,TEMP_MIN_LIMIT ,
                               TEMP_MIN_LIMIT,(TEMP_MIN_LIMIT + 0.05 * TEMP_MAX_LIMIT), 
                               (TEMP_MIN_LIMIT + 0.05 * TEMP_MAX_LIMIT) ,(TEMP_MAX_LIMIT - 0.05 * TEMP_MAX_LIMIT ),
                               (TEMP_MAX_LIMIT - 0.05 * TEMP_MAX_LIMIT ),TEMP_MAX_LIMIT,
                               TEMP_MAX_LIMIT,100 };

ParameterRange SOCRange  = {0,SOC_MIN_LIMIT,
                       SOC_MIN_LIMIT, (SOC_MIN_LIMIT + 0.05 * SOC_MAX_LIMIT),
                       (SOC_MIN_LIMIT + 0.05 * SOC_MAX_LIMIT) , (SOC_MAX_LIMIT - 0.05 * SOC_MAX_LIMIT ),
                       (SOC_MAX_LIMIT - 0.05 * SOC_MAX_LIMIT ), SOC_MAX_LIMIT,
                       SOC_MAX_LIMIT,100   
                       };

ParameterRange ChargeRateRange =  {0,CHARGERATE_MIN_LIMIT,
                                   CHARGERATE_MIN_LIMIT, (CHARGERATE_MIN_LIMIT + 0.05 * CHARGERATE_MAX_LIMIT),
                                   (CHARGERATE_MIN_LIMIT + 0.05 * CHARGERATE_MAX_LIMIT) , (CHARGERATE_MAX_LIMIT - 0.05 * CHARGERATE_MAX_LIMIT ),
                                   (CHARGERATE_MAX_LIMIT - 0.05 * CHARGERATE_MAX_LIMIT ), CHARGERATE_MAX_LIMIT,
                                   CHARGERATE_MAX_LIMIT,1
                                   };

void PrintOnConsole( char message[]);

int IsThresholdBreached(float parameter, ParameterRange range);

int IsAtLowerWarningLevel(float parameter, ParameterRange range);

int IsAtHigherWarningLevel(float parameter, ParameterRange range);

BatteryStatus CheckBatteryStatus(BatteryTestData testdata);

void AssertBatteryIsOk(BatteryStatus result,int expectedresult);
