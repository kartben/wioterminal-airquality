#include <Arduino.h>
#include <rpcWiFi.h>

#include "config.h"

#include <ArduinoHA.h>

#define BROKER_ADDR IPAddress(192,168,1,157)

#include "wifi_credentials.h"
const char* ssid = WIFI_SSID;
const char* password =  WIFI_PASSWORD;

byte mac[] = {0x00, 0x10, 0xFA, 0x6E, 0x38, 0x4B};
HADevice device(mac, sizeof(mac));
WiFiClient client;
HAMqtt mqtt(client, device);
 

#ifdef MONITOR_BATTERY
#include <SparkFunBQ27441.h>
const unsigned int BATTERY_CAPACITY = 650; // Set Wio Terminal Battery's Capacity 
void setupBQ27441(void)
{
  // Use lipo.begin() to initialize the BQ27441-G1A and confirm that it's
  // connected and communicating.
  if (!lipo.begin()) // begin() will return true if communication is successful
  {
  // If communication fails, print an error message and loop forever.
    Serial.println("Error: Unable to communicate with BQ27441.");
    Serial.println("  Check wiring and try again.");
    Serial.println("  (Battery must be plugged into Battery Babysitter!)");
    while (1) ;
  }
  Serial.println("Connected to BQ27441!");
 
  // Uset lipo.setCapacity(BATTERY_CAPACITY) to set the design capacity
  // of your battery.
  lipo.setCapacity(BATTERY_CAPACITY);
}

HASensor batteryLevel("wio_aiq_battery_level");
HASensor batteryVoltage("wio_aiq_battery_voltage");
#endif

#ifdef MONITOR_SCD30
#include "SCD30.h"
#define SERIAL SerialUSB

HASensor co2("wio_aiq_co2");
HASensor temperature("wio_aiq_temperature");
HASensor humidity("wio_aiq_humidity");
#endif

#ifdef MONITOR_HM3301
#include <Tomoto_HM330X.h>
Tomoto_HM330X sensor;

HASensor pm1("wio_aiq_x");
HASensor pm25("wio_aiq_y");
HASensor pm10("wio_aiq_z");
#endif

 
void setup() {
    Wire.begin();
    Serial.begin(115200);

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(1000);
 
    WiFi.begin(ssid, password);
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
    Serial.print("IP Address: ");
    Serial.println (WiFi.localIP()); // prints out the device's IP address


    // set device's details (optional)
    device.setName("Wio Terminal - Air Quality Monitor");
    device.setManufacturer("Seeed Studio");
    device.setModel("Wio Terminal");
    device.setSoftwareVersion("1.0.0");

    #ifdef MONITOR_BATTERY
    setupBQ27441();

    batteryLevel.setDeviceClass("battery");
    batteryLevel.setIcon("mdi:battery");
    batteryLevel.setName("Battery level");
    batteryLevel.setUnitOfMeasurement("%");

    batteryVoltage.setDeviceClass("voltage");
    batteryVoltage.setIcon("mdi:battery");
    batteryVoltage.setName("Battery voltage");
    batteryVoltage.setUnitOfMeasurement("mV");
    #endif

    #ifdef MONITOR_SCD30
    scd30.initialize();

    co2.setDeviceClass("carbon_dioxide");
    co2.setIcon("mdi:molecule-co2");
    co2.setName("CO2");
    co2.setUnitOfMeasurement("ppm");

    temperature.setDeviceClass("temperature");
    temperature.setIcon("mdi:thermometer");
    temperature.setName("Temperature");
    temperature.setUnitOfMeasurement("°C");

    humidity.setDeviceClass("humidity");
    humidity.setIcon("mdi:water-percent");
    humidity.setName("Humidity");
    humidity.setUnitOfMeasurement("%");
   #endif

    #ifdef MONITOR_HM3301
    if (!sensor.begin()) {
    Serial.println("Failed to initialize HM330X");
    while (1)
      ;

    pm1.setDeviceClass("pm1");
    pm1.setIcon("mdi:weather-dust");
    pm1.setName("x");
    pm1.setUnitOfMeasurement("ug/m3");

    pm25.setDeviceClass("humidity");
    pm25.setIcon("mdi:weather-dust");
    pm25.setName("y");
    pm25.setUnitOfMeasurement("ug/m3");

    pm10.setDeviceClass("pm10");
    pm10.setIcon("mdi:weather-dust");
    pm10.setName("z");
    pm10.setUnitOfMeasurement("ug/m3");   
    #endif
  }

    mqtt.begin(BROKER_ADDR);
}
 
 
void loop() {
    // put your main code here, to run repeatedly:
    mqtt.loop();

    #ifdef MONITOR_BATTERY
    // Read the battery voltage
    batteryLevel.setValue(String(lipo.soc()).c_str());
    batteryVoltage.setValue(String(lipo.voltage()).c_str());
    #endif

    #ifdef MONITOR_SCD30
    // Read the CO2, temperature and humidity
    float result[3] = {0};

    if (scd30.isAvailable()) {
        scd30.getCarbonDioxideConcentration(result);

        co2.setValue(String(result[0]).c_str());
        temperature.setValue(String(result[1]).c_str());
        humidity.setValue(String(result[2]).c_str());
    }
    #endif

    #ifdef MONITOR_HM3301
    // Read the PM1, PM2.5 and PM10
    if(sensor.readSensor()) {
        pm1.setValue(String(sensor.atm.getPM1()).c_str());
        pm25.setValue(String(sensor.atm.getPM2_5()).c_str());
        pm10.setValue(String(sensor.atm.getPM10()).c_str());
    }
    #endif


    delay(5000);
}
