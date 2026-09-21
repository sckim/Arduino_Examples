#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 3

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup()
{
    Serial.begin(9600);
    sensors.begin();

    // 연결된 센서 개수 확인
    int deviceCount = sensors.getDeviceCount();
    Serial.print("Found ");
    Serial.print(deviceCount);
    Serial.println(" devices.");

    // 각 센서의 주소 출력
    DeviceAddress deviceAddress;
    for (int i = 0; i < deviceCount; i++)
    {
        if (sensors.getAddress(deviceAddress, i))
        {
            Serial.print("Device ");
            Serial.print(i);
            Serial.print(" Address: ");
            for (uint8_t j = 0; j < 8; j++)
            {
                if (deviceAddress[j] < 16)
                    Serial.print("0");
                Serial.print(deviceAddress[j], HEX);
                Serial.print(" ");
            }
            Serial.println();
        }
    }

    // OneWire 버스 직접 스캔
    Serial.println("\nDirect OneWire scan:");
    oneWire.reset_search();
    uint8_t addr[8];
    int count = 0;
    while (oneWire.search(addr))
    {
        Serial.print("ROM = ");
        for (int i = 0; i < 8; i++)
        {
            if (addr[i] < 16)
                Serial.print("0");
            Serial.print(addr[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
        count++;
    }
    Serial.print("Direct scan found: ");
    Serial.println(count);
}

void loop()
{
    sensors.requestTemperatures();
    delay(750); // 온도 변환 완료 대기

    float tempC = sensors.getTempCByIndex(0);

    // 재시도 로직 추가
    int retryCount = 0;
    while (tempC == DEVICE_DISCONNECTED_C && retryCount < 3)
    {
        // delay(100);
        sensors.requestTemperatures();
        delay(750);
        tempC = sensors.getTempCByIndex(0);
        retryCount++;
    }

    if (tempC == DEVICE_DISCONNECTED_C)
    {
        Serial.println("Sensor communication error after retries.");
    }
    else
    {
        Serial.print("Temperature: ");
        Serial.print(tempC);
        Serial.println(" °C");
    }
    delay(250);
}