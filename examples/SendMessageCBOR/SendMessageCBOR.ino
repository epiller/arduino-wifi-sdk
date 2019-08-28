/* AllThingsTalk Arduino SDK
 * https://github.com/allthingstalk/arduino-sdk-v2
 *
 * About this example: 
 * Increments a counter from 0 (by 1) and uploads the new value to your AllThingsTalk Maker.
 * Value is uploaded using CBOR sending method.
 * Process is repeated every 5 seconds.
 *
 * Notes:
 * - Create a device on your https://maker.allthingstalk.com (if you don't already have it)
 * - Create a Sensor asset of type Integer on your AllThingsTalk Maker.
 *   You'll receive the value on this asset.
 * - Change the following things in this example to make it work:
 *   WiFi-SSID, WiFi-Password, Device-ID, Device-Token, Sensor-Asset
 */

#include <AllThingsTalk.h>

auto wifiCreds   = WifiCredentials("WiFi-SSID", "WiFi-Password"); // Your WiFi Network Name and Password
auto deviceCreds = DeviceConfig("Device-ID", "Device-Token");     // Go to AllThingsTalk Maker > Devices > Your Device > Settings > Authentication to get your Device ID and Token
auto device      = Device(wifiCreds, deviceCreds);                // Create "device" object
CborPayload payload;                                              // Create CBOR payload object, so we can use CBOR sending

int value = 0;                 // Initial value of counter

void setup() {
  Serial.begin(115200);        // Baud rate: 115200, but you can define any baud rate you want   
  device.debugPort(Serial);    // Set AllThingsTalk library to output its debug to "Serial"
  device.init();               // Initialize AllThingsTalk
}

void loop() {
  device.loop();               // Keep AllThingsTalk & WiFi Alive
  ++value;                     // Increment the value by 1
  payload.reset();             // Reset the payload
  payload.set("Sensor-Asset", value);  // Set "value" (counter) to be sent to "Sensor-Asset" asset (change this)
  device.send(payload);        // Send the payload
  delay(5000);                 // Wait 5 seconds until repeating
}