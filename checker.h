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

tyedef struct{
  float lowlimit;
  float highlimit;
}RANGE;

RANGE TemperatureLowBreach = {0,TEMP_MIN_LIMIT};
RANGE TemperatureLowWarning = {TEMP_MIN_LIMIT, (TEMP_MIN_LIMIT + 0.05 * TEMP_MAX_LIMIT)}; //5%
RANGE TemperatureNormal = {(TEMP_MIN_LIMIT + 0.05 * TEMP_MAX_LIMIT) , (TEMP_MAX_LIMIT - 0.05 * TEMP_MAX_LIMIT )};
RANGE TemperatureHighWarning = {(TEMP_MAX_LIMIT - 0.05 * TEMP_MAX_LIMIT ), TEMP_MAX_LIMIT}; //5%
RANGE TemperatureHighBreach = {TEMP_MAX_LIMIT,100};

RANGE SOCLowBreach = {0,SOC_MIN_LIMIT};
RANGE SOCLowWarning = {SOC_MIN_LIMIT, (SOC_MIN_LIMIT + 0.05 * SOC_MAX_LIMIT)}; //5%
RANGE SOCNormal = {(SOC_MIN_LIMIT + 0.05 * SOC_MAX_LIMIT) , (SOC_MAX_LIMIT - 0.05 * SOC_MAX_LIMIT )};
RANGE SOCHighWarning = {(SOC_MAX_LIMIT - 0.05 * SOC_MAX_LIMIT ), SOC_MAX_LIMIT}; //5%
RANGE SOCHighBreach = {SOC_MAX_LIMIT,100};

RANGE ChargeRateLowBreach = {0,CHARGERATE_MIN_LIMIT};
RANGE ChargeRateLowWarning = {CHARGERATE_MIN_LIMIT, (CHARGERATE_MIN_LIMIT + 0.05 * CHARGERATE_MAX_LIMIT)}; //5%
RANGE ChargeRateNormal = {(CHARGERATE_MIN_LIMIT + 0.05 * CHARGERATE_MAX_LIMIT) , (CHARGERATE_MAX_LIMIT - 0.05 * CHARGERATE_MAX_LIMIT )};
RANGE ChargeRateHighWarning = {(CHARGERATE_MAX_LIMIT - 0.05 * CHARGERATE_MAX_LIMIT ), CHARGERATE_MAX_LIMIT}; //5%
RANGE ChargeRateHighBreach = {CHARGERATE_MAX_LIMIT,100};

void PrintOnConsole( char message[]);

int IsParameterInRange(float parameter, float minvalue , float maxvalue , char parametername[]);

int CheckBatteryStatus(BatteryTestData testdata);

void AssertBatteryIsOk(int result,int expectedresult);
