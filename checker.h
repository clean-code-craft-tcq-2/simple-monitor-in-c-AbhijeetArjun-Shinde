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
  float lowlimit;
  float highlimit;
}range;

range TemperatureLowBreach = {0,TEMP_MIN_LIMIT};
range TemperatureLowWarning = {TEMP_MIN_LIMIT, (TEMP_MIN_LIMIT + 0.05 * TEMP_MAX_LIMIT)}; //5%
range TemperatureNormal = {(TEMP_MIN_LIMIT + 0.05 * TEMP_MAX_LIMIT) , (TEMP_MAX_LIMIT - 0.05 * TEMP_MAX_LIMIT )};
range TemperatureHighWarning = {(TEMP_MAX_LIMIT - 0.05 * TEMP_MAX_LIMIT ), TEMP_MAX_LIMIT}; //5%
range TemperatureHighBreach = {TEMP_MAX_LIMIT,100};

range SOCLowBreach = {0,SOC_MIN_LIMIT};
range SOCLowWarning = {SOC_MIN_LIMIT, (SOC_MIN_LIMIT + 0.05 * SOC_MAX_LIMIT)}; //5%
range SOCNormal = {(SOC_MIN_LIMIT + 0.05 * SOC_MAX_LIMIT) , (SOC_MAX_LIMIT - 0.05 * SOC_MAX_LIMIT )};
range SOCHighWarning = {(SOC_MAX_LIMIT - 0.05 * SOC_MAX_LIMIT ), SOC_MAX_LIMIT}; //5%
range SOCHighBreach = {SOC_MAX_LIMIT,100};

range ChargeRateLowBreach = {0,CHARGERATE_MIN_LIMIT};
range ChargeRateLowWarning = {CHARGERATE_MIN_LIMIT, (CHARGERATE_MIN_LIMIT + 0.05 * CHARGERATE_MAX_LIMIT)}; //5%
range ChargeRateNormal = {(CHARGERATE_MIN_LIMIT + 0.05 * CHARGERATE_MAX_LIMIT) , (CHARGERATE_MAX_LIMIT - 0.05 * CHARGERATE_MAX_LIMIT )};
range ChargeRateHighWarning = {(CHARGERATE_MAX_LIMIT - 0.05 * CHARGERATE_MAX_LIMIT ), CHARGERATE_MAX_LIMIT}; //5%
range ChargeRateHighBreach = {CHARGERATE_MAX_LIMIT,100};

void PrintOnConsole( char message[]);

int IsParameterInRange(float parameter, float minvalue , float maxvalue , char parametername[]);

int CheckBatteryStatus(BatteryTestData testdata);

void AssertBatteryIsOk(int result,int expectedresult);
