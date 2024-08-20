# Automatic Plant Watering System

This project is an automatic plant watering system based on NodeMCU (ESP8266) integrated with Blynk. The system monitors soil moisture, temperature, and light intensity in real-time and automatically controls the water pump to maintain optimal soil moisture for plants.

[![My Skills](https://skillicons.dev/icons?i=arduino,cpp)](https://skillicons.dev)

## Features

- **Soil Moisture Monitoring:** Automatically waters the plant when the soil moisture is below the threshold.
- **Temperature Monitoring:** Measures and displays ambient temperature.
- **Light Intensity Monitoring:** Monitors surrounding light levels.
- **Remote Control:** Use Blynk to monitor and control the system from a smartphone.

## Required Components

- NodeMCU (ESP8266)
- Soil Moisture Sensor
- Temperature and Humidity Sensor (DHT11)
- Light Sensor (LDR)
- 5V Relay Module
- Water Pump
- LCD Display (I2C)
- Jumper Wires and Breadboard

## Table Wiring System

### ESP8266 to Breadboard

| ESP8266 | Breadboard |
|---------|------------|
| VIN     | +          |
| G / GND | -          |

### Soil Moisture Sensor

| Soil Moisture | Breadboard/ESP8266 |
|---------------|-------------------|
| VCC           | +                 |
| GND           | -                 |
| A0            | A0                |

### ESP8266 to Relay

| ESP8266 | Relay |
|---------|-------|
| 3V      | VCC   |
| GND     | GND   |
| D1      | IN    |

### Temperature Sensor

| Temperature | Breadboard/ESP8266 |
|-------------|-------------------|
| VCC         | 3V                |
| GND         | GND               |
| OUT         | D5                |

### Light Sensor (LDR)

| Light Sensor | Breadboard/ESP8266 |
|--------------|-------------------|
| VCC          | 3V                |
| GND          | GND               |
| D0           | D0                |

### LCD Display

| LCD  | Breadboard/ESP8266 |
|------|-------------------|
| VCC  | VU                |
| GND  | GND               |
| SDA  | D3                |
| SCL  | D4                |

## Circuit Diagram
> **Note:** The circuit diagram provided is for reference only. The actual wiring and components may differ slightly from the diagram shown here.

<p align="center">
  <img src="https://github.com/user-attachments/assets/aba2ce81-c11a-4425-8e75-4305568c6bc4" alt="Circuit Diagram">
</p>


## Installation and Usage

### 1. Blynk Setup

1. Download and install the Blynk app on your smartphone.
2. Create a new project and save the Blynk Authentication Token.
3. Configure widgets to display soil moisture (V0), temperature (V2), light intensity (V5), and system status.

>![image](https://github.com/user-attachments/assets/69ed4c82-7508-40ca-8709-99e3d5789ea6)



### 2. Arduino IDE Setup

1. Install the `ESP8266` board manager and required libraries:
   - `ESP8266WiFi`
   - `BlynkSimpleEsp8266`
   - `DHT`
   - `LiquidCrystal_I2C`
2. Clone or download this repository.
3. Open the `automatic-plant-watering-system.ino` file in the Arduino IDE.
4. Replace the following placeholders with your information:

```cpp
#define BLYNK_TEMPLATE_ID "TMPL66kiHzN1Z"                   // Blynk Template ID
#define BLYNK_TEMPLATE_NAME "NODEMCU"                       // Blynk Template Name
#define BLYNK_AUTH_TOKEN "oiBE1CCufW5esOqp5YsPoACPejVX7GP8" // Blynk Auth Token

char auth[] = "oiBE1CCufW5esOqp5YsPoACPejVX7GP8"; // Blynk Auth Token
char ssid[] = "Your_WiFi_Name";                   // Your WiFi Name
char pass[] = "Your_WiFi_Password";               // Your WiFi Password
