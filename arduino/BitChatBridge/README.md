# BitChat Bridge (Arduino)

This sketch demonstrates basic Bluetooth Low Energy communication with the BitChat mesh network.

It exposes the same BLE service and characteristic UUIDs used by the BitChat app:

- Service UUID: `F47B5E2D-4A9E-4C5A-9B3F-8E1D2C3A4B5C`
- Characteristic UUID: `A1B2C3D4-E5F6-4A5B-8C9D-0E1F2A3B4C5D`

The example advertises as a peripheral. When a BitChat node connects and writes data to the characteristic, the sketch logs the message to the serial console and replies with a simple text message. The first byte of each packet is the BitChat message type (0x04 for user messages).

## Hardware

Any Arduino board with BLE support (e.g., Nano 33 BLE, ESP32 running Arduino core).

## Usage

1. Compile and upload `BitChatBridge.ino` to your board.
2. Open the serial monitor at 115200 baud.
3. Launch BitChat and ensure Bluetooth is enabled.
4. The app should discover the Arduino node as another peer.
5. Messages sent from the app will appear in the serial monitor; the sketch sends back a greeting.

This is a minimal example—real integration would implement the full BitChat binary protocol for routing and encryption.
