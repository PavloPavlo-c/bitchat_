#include <ArduinoBLE.h>

// BitChat BLE UUIDs
const char* serviceUUID = "F47B5E2D-4A9E-4C5A-9B3F-8E1D2C3A4B5C";
const char* characteristicUUID = "A1B2C3D4-E5F6-4A5B-8C9D-0E1F2A3B4C5D";

BLEService chatService(serviceUUID);                       // BitChat mesh service
BLECharacteristic chatCharacteristic(characteristicUUID,
                                     BLERead | BLEWrite | BLENotify, 244);

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }

  BLE.setLocalName("BitChatBridge");
  BLE.setAdvertisedService(chatService);

  chatService.addCharacteristic(chatCharacteristic);
  BLE.addService(chatService);

  chatCharacteristic.writeValue((uint8_t*)"", 0); // initialize

  BLE.advertise();
  Serial.println("BitChat bridge ready");
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected to ");
    Serial.println(central.address());

    while (central.connected()) {
      if (chatCharacteristic.written()) {
        int len = chatCharacteristic.valueLength();
        uint8_t buffer[244];
        chatCharacteristic.readValue(buffer, len);

        Serial.print("Received ");
        Serial.print(len);
        Serial.print(" bytes: ");
        for (int i = 0; i < len; i++) {
          Serial.print(buffer[i], HEX);
          Serial.print(' ');
        }
        Serial.println();

        // Reply with simple user message (type 0x04)
        const char* msg = "Hello from Arduino";
        uint8_t packet[1 + 32];
        packet[0] = 0x04; // MessageType.message
        size_t msgLen = strlen(msg);
        memcpy(packet + 1, msg, msgLen);
        chatCharacteristic.writeValue(packet, msgLen + 1);
      }
    }

    Serial.println("Disconnected");
  }
}
