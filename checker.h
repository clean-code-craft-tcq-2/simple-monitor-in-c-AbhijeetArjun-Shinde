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



void PrintOnConsole( char message[]);

int TestBatteryTempIsOk(float temperature);

int TestBatterySocIsOk(float soc);

int TestBatteryChargeRateIsOk(float chargeRate);

void AssertBatteryIsOk(BatteryTestData testdata , int result);
