# Smart Inhaler System

## IoT-Based Asthma Management Solution for Bangladesh

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform](https://img.shields.io/badge/Platform-ESP8266-blue)](https://www.espressif.com/)
[![Arduino](https://img.shields.io/badge/Arduino-Compatible-green)](https://www.arduino.cc/)

---

## Table of Contents
- [Problem Statement](#problem-statement)
- [Our Solution](#our-solution)
- [Features](#features)
- [System Architecture](#system-architecture)
- [Hardware Components](#hardware-components)
- [Software Requirements](#software-requirements)
- [Installation Guide](#installation-guide)
- [Circuit Diagram](#circuit-diagram)
- [Cost Analysis](#cost-analysis)
- [Usage](#usage)
- [API Documentation](#api-documentation)

---

## Problem Statement

Asthma affects **7% of Bangladesh's population** (approximately 11.9 million people), with particularly high prevalence among children and urban populations due to:
- High air pollution levels
- Dust and particulate matter
- High humidity (60-90% year-round)
- Rapid urbanization

### Current Challenges in Inhaler Usage:

| Challenge | Impact |
|-----------|---------|
| **Incorrect Usage Technique** | 70% of patients use inhalers incorrectly, reducing medicine efficacy |
| **Poor Adherence** | 50% of patients miss doses or take incorrect dosages |
| **No Digital Tracking** | No way to monitor usage patterns or medication history |
| **Environmental Correlation Gap** | Cannot correlate attacks with environmental triggers |
| **Untracked Emergencies** | Emergency usage often goes unreported |

### Existing Solutions & Limitations:

1. **FindAir SmartHaler** (€89/~$95)
   - Still in testing phase
   - Too expensive for Bangladesh market
   - Limited availability

2. **Smart Inhaler Add-on** ($40)
   - Not locally available
   - Requires smartphone connectivity
   - No environmental monitoring

---

##  Our Solution

<img src="https://github.com/WinTer1165/Digital-Inhaler/blob/main/images/IMG_0572.jpg?raw=true" alt="Device Photo 1" style="width:300px;"/>
<img src="https://github.com/WinTer1165/Digital-Inhaler/blob/main/images/IMG_0573.jpg?raw=true" alt="Device Photo 2" style="width:300px;"/>
<img src="https://github.com/WinTer1165/Digital-Inhaler/blob/main/images/IMG_0574.jpg?raw=true" alt="Device Photo 3" style="width:300px;"/>

A **locally-manufactured, affordable IoT smart inhaler system** designed specifically for Bangladesh's healthcare ecosystem.

### Key Differentiators:
-  **Affordable**: Target price under $15 (BDT 1,800)
-  **Local Manufacturing**: Can be produced in Bangladesh
-  **Environmental Monitoring**: Real-time air quality tracking
-  **Offline Capability**: Works without constant internet

---

##  Features

![Demo GIF](https://github.com/WinTer1165/Digital-Inhaler/blob/main/images/demo.gif?raw=true)

<img src="https://github.com/WinTer1165/Digital-Inhaler/blob/main/images/ui.png?raw=true" alt="UI/UX" style="width:900px;"/>


### Core Features
-  **Puff Detection & Counting**: Accurate force-sensitive resistor (FSR) based detection
-  **Real-time Web Dashboard**: Monitor usage from any device
-  **Environmental Monitoring**: Temperature, humidity, air quality, and pressure tracking
-  **Smart Medication Reminders**: Customizable alerts for medication schedules
-  **Usage Analytics**: 7-day history with graphical visualization
-  **Find My Inhaler**: Buzzer and vibration for locating misplaced device
-  **Offline Data Storage**: EEPROM-based storage for offline usage
-  **Auto Time Sync**: NTP-based time synchronization

### Advanced Features
- **Asthma Risk Assessment**: Risk calculation using environmental factors
- **WebSocket Real-time Updates**: Live data streaming to connected devices
- **Maximum Dosage Alerts**: Warns when approaching daily limits
- **Emergency Detection**: Identifies unusual usage patterns

---

##  System Architecture

```
┌─────────────────────────────────────────────────────────┐
│                    Smart Inhaler Device                 │
├─────────────────────────────────────────────────────────┤
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌─────────┐  │
│  │   FSR    │  │  BME280  │  │  MQ-135  │  │  OLED   │  │
│  │ (Puff)   │  │(Env Data)│  │(Air Qual)│  │(Display)│  │
│  └────┬─────┘  └────┬─────┘  └────┬─────┘  └────┬────┘  │
│       │             │             │              │      │
│  ┌────▼─────────────▼─────────────▼──────────────▼────┐ │
│  │              ESP8266 NodeMCU                       │ │
│  │   ┌──────────────────────────────────────────┐     │ │
│  │   │ • Sensor Data Processing                 │     │ │
│  │   │ • Web Server (Port 80)                   │     │ │
│  │   │ • WebSocket Server (Port 81)             │     │ │
│  │   │ • EEPROM Storage Management              │     │ │
│  │   └──────────────────────────────────────────┘     │ │
│  └─────────────────────┬──────────────────────────────┘ │
│                        │                                │
└────────────────────────┼────────────────────────────────┘
                         │
                    WiFi │ 802.11 b/g/n
                         │
           ┌─────────────▼──────────────┐
           │      Local Network         │
           │   ┌──────────────────┐     │
           │   │   Web Interface  │     │
           │   │  (Responsive UI) │     │
           │   └──────────────────┘     │
           └────────────────────────────┘
```

---

##  Hardware Components

### Required Components

| Component | Model | Quantity | Purpose | Approx. Cost (BDT) |
|-----------|-------|----------|---------|-------------------|
| **Microcontroller** | ESP8266 NodeMCU | 1 | Main processor with WiFi | 650 |
| **Force Sensor** | FSR 402 | 1 | Puff detection | 645 |
| **Environmental Sensor** | BME280 | 1 | Temp, humidity, pressure | 490 |
| **Air Quality Sensor** | MQ-135 | 1 | Air quality monitoring | 174 |
| **Display** | 0.96" OLED I2C | 1 | Local display | 290 |
| **RTC Module** | DS3231 | 1 | Time keeping | 250 |
| **Buzzer** | Active 5V | 1 | Audio alerts | 50 |
| **Vibration Motor** | 3V Mini | 1 | Haptic feedback | 100 |
| **Resistor** | 10kΩ | 1 | Pull-down for FSR | 5 |
| **Wires & PCB** | - | - | Connections | 200 |
| **Enclosure** | 3D Printed | 1 | Device housing | 200 |
| **Battery** | Li-Po 3.7V 1000mAh | 1 | Power supply | 250 |

**Total Development Cost: ~BDT 3500 ($29.50)**

### Pin Connections

```
ESP8266 NodeMCU Pin Configuration:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
A0  ← FSR (with 10kΩ pull-down to GND)
D1  → I2C SCL (BME280, OLED, RTC)
D2  → I2C SDA (BME280, OLED, RTC)
D5  ← MQ-135 Digital Output
D6  → Buzzer Signal
D7  → Vibration Motor Signal
3V3 → Power for I2C devices
5V  → Power for MQ-135
GND → Common Ground
```

---

##  Software Requirements

### Development Environment
- **Arduino IDE** v1.8.19 or higher
- **ESP8266 Board Package** 

### Required Libraries
```cpp
// Install via Arduino Library Manager:
ESP8266WiFi         // Built-in
ESP8266WebServer    // Built-in
WebSocketsServer    // v2.3.6 by Markus Sattler
Wire                // Built-in
Adafruit_Sensor     // v1.1.4
Adafruit_BME280     // v2.2.2
RTClib              // v2.0.3
Adafruit_GFX        // v1.11.3
Adafruit_SSD1306    // v2.5.7
ArduinoJson         // v6.19.4
NTPClient           // v3.2.1
```

---

##  Installation Guide
<img src="https://raw.githubusercontent.com/WinTer1165/Digital-Inhaler/bda6932cfa721df9af1bc6edc74ee1808390fdb8/images/circuit-schematic.svg" alt="Circuit Diagram" style="width:600px;"/>

###  1. Hardware Setup

1. Assemble components according to the circuit diagram
2. Ensure all I2C devices have unique addresses:
   - BME280: 0x76 or 0x77
   - OLED: 0x3C
   - RTC: 0x68

### 2. Software Setup

```bash
# Clone the repository
git clone https://github.com/WinTer1165/Digital-Inhaler.git
cd digital-inhaler/smartinhaler

# Open in Arduino IDE
# File → Open → SmartInhaler.ino
```

### 3. Configuration
Edit `config.h` to set your WiFi credentials:
```cpp
const char* WIFI_SSID = "Set_WiFi_Name";
const char* WIFI_PASSWORD = "Set_WiFi_Password";
```

### 4. Upload Code
1. Select Board: `Tools → Board → NodeMCU 1.0 (ESP-12E Module)`
2. Select Port: `Tools → Port → COMx` (or `/dev/ttyUSBx` on Linux)
3. Click Upload

### 5. Access Web Interface
1. Open Serial Monitor (115200 baud)
2. Note the IP address displayed
3. Open browser and navigate to: `http://[IP_ADDRESS]`

---

## Circuit Diagram

See the included circuit schematic for detailed wiring instructions. Key connections:
- All I2C devices share SCL (D1) and SDA (D2) lines
- FSR requires a 10kΩ pull-down resistor
- MQ-135 requires 5V power supply
- Use level shifters if needed for 5V/3.3V compatibility

---

## Cost Analysis

### Development Cost (Prototype)
| Category | Cost (BDT) | Cost (USD) |
|----------|------------|------------|
| Components | 3,600 | $30.00 |
| Assembly | 400 | $3.33 |
| **Total** | **4000** | **$33.33** |

### Production Cost (Scale: 1000 units)
| Category | Cost (BDT) | Cost (USD) |
|----------|------------|------------|
| Components (bulk) | 800 | $6.66 |
| PCB (mass production) | 100 | $0.83 |
| Injection molding | 100 | $0.83 |
| Assembly | 50 | $0.41 |
| **Total** | **1,050** | **$8.73** |

### Comparison with Existing Solutions
| Product | Price | Availability | Features |
|---------|-------|--------------|----------|
| **Our Solution** | $8-15 | Local | Full environmental monitoring |
| FindAir SmartHaler | $95 | Import only | Limited features |
| Generic Add-on | $40 | Not available | Basic tracking only |

---

## Usage

### Initial Setup
1. Power on the device
2. Connect to WiFi network (automatic)
3. Access web dashboard
4. Set medication reminders
5. Configure max puff limits

### Daily Usage
- **Normal Use**: Simply use the inhaler as usual - puffs are automatically detected
- **Check Stats**: View daily/weekly usage on OLED display
- **Web Dashboard**: Access detailed analytics from any device
- **Reminders**: Device will buzz/vibrate at medication times

---

## API Documentation

### WebSocket Events

#### Receive Events
```javascript
// Sensor Data Update
{
  "type": "sensorData",
  "temperature": 25.5,
  "humidity": 65,
  "airQuality": 85,
  "pressure": 1013,
  "totalPuffs": 120,
  "dailyPuffs": 4
}

// Puff Detected
{
  "type": "puffDetected",
  "totalPuffs": 121,
  "timestamp": "14:23:45"
}
```

#### Send Commands
```javascript
// Set Reminder
{
  "command": "setReminder",
  "index": 0,
  "hour": 8,
  "minute": 30,
  "label": "Morning dose"
}

// Reset Counter
{
  "command": "resetPuffs"
}

// Get Usage History
{
  "command": "getHistory"
}
```
