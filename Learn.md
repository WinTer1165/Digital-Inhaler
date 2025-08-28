# Learn - Smart Inhaler System

## What You'll Learn

### **Basic Skills**
- How to connect sensors to ESP8266
- Simple web server programming
- Reading sensor data
- Creating basic web pages

### **Components Used**
- ESP8266 microcontroller (brain of the device)
- FSR sensor (detects inhaler puffs)
- BME280 sensor (temperature, humidity)
- OLED display (shows information)
- Buzzer (makes sounds for reminders)

---

## Prerequisites

**You should know:**
- Basic programming (variables, loops, functions)
- Simple electronics (connecting wires)
- How to use Arduino IDE

**You'll need:**
- Computer with Arduino IDE
- ESP8266 board and sensors (Check Readme.md)
- Breadboard and wires

---

## Key Concepts

### 1. **ESP8266 Basics**
The ESP8266 is like a small computer with WiFi. It can:
- Read sensors
- Connect to internet
- Run a simple website
- Store data

```cpp
void setup() {
  Serial.begin(115200);  // Start communication
  WiFi.begin(ssid, password);  // Connect to WiFi
}
```

### 2. **Reading Sensors**
Sensors give us numbers that represent real-world things:

```cpp
// Read temperature sensor
float temperature = bme.readTemperature();
Serial.println("Temperature: " + String(temperature));

// Read puff sensor
int puffValue = analogRead(A0);
if (puffValue > 100) {
  Serial.println("Puff detected!");
}
```

### 3. **Simple Web Server**
Create a webpage that shows sensor data:

```cpp
server.on("/", [](){
  String webpage = "<h1>My Inhaler</h1>";
  webpage += "<p>Temperature: " + String(temperature) + "</p>";
  server.send(200, "text/html", webpage);
});
```

### 4. **Storing Data**
Save information so it doesn't disappear when device restarts:

```cpp
#include <EEPROM.h>

// Save puff count
int puffCount = 0;
EEPROM.put(0, puffCount);  // Save to memory
EEPROM.get(0, puffCount);  // Read from memory
```

---

## Learning Steps

### **Step 1: Basic Setup** (30 minutes)
1. Connect ESP8266 to computer
2. Install Arduino IDE
3. Upload simple "Hello World" program
4. Check serial monitor for output

### **Step 2: Connect One Sensor** (1 hour)
1. Connect BME280 sensor
2. Read temperature and humidity
3. Print values to serial monitor
4. Understand I2C communication

### **Step 3: Create Web Page** (1 hour)
1. Connect ESP8266 to WiFi
2. Create simple web server
3. Show sensor data on webpage
4. Access from phone/computer browser

### **Step 4: Add Puff Detection** (1 hour)
1. Connect FSR sensor
2. Detect when someone uses inhaler
3. Count puffs
4. Show count on display

### **Step 5: Add Features** (2 hours)
1. Add buzzer for reminders
2. Store data permanently
3. Create better web interface
4. Add real-time updates

---

## Simple Exercises

### **Exercise 1: Sensor Reading**
```cpp
// Read and display sensor data every 2 seconds
void loop() {
  float temp = bme.readTemperature();
  Serial.println("Temperature: " + String(temp));
  delay(2000);
}
```

### **Exercise 2: Puff Counter**
```cpp
int puffCount = 0;

void loop() {
  int sensor = analogRead(A0);
  if (sensor > 100) {
    puffCount++;
    Serial.println("Puffs today: " + String(puffCount));
    delay(1000); // Wait to avoid multiple counts
  }
}
```

### **Exercise 3: Simple Web Page**
```cpp
void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Smart Inhaler</h1>";
  html += "<p>Puffs today: " + String(puffCount) + "</p>";
  html += "<p>Temperature: " + String(temperature) + "°C</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}
```

---

## What Each Part Does

### **Hardware Components**
- **ESP8266**: Main brain, handles WiFi and processing
- **FSR Sensor**: Detects when inhaler is pressed
- **BME280**: Measures temperature, humidity, air pressure  
- **OLED Display**: Shows information on small screen
- **Buzzer**: Makes sounds for medication reminders

### **Software Parts**
- **Arduino Code**: Instructions for the ESP8266
- **Web Server**: Creates a website hosted on the device
- **Sensor Libraries**: Pre-written code to read sensors
- **WiFi Connection**: Connects device to internet

---

## Common Problems & Solutions

### **WiFi Not Connecting**
- Check WiFi name and password
- Make sure device is close to router
- Restart ESP8266

### **Sensor Not Working**  
- Check wire connections
- Verify sensor address (for I2C devices)
- Test with simple example code

### **Webpage Not Loading**
- Check IP address in serial monitor
- Make sure computer is on same WiFi network
- Try restarting the ESP8266

---

## Next Steps

Once you understand the basics:

1. **Add more sensors** (air quality, light)
2. **Improve the website** (add colors, graphs)
3. **Create mobile app** (using simple tools)
4. **Add data logging** (save data over time)
5. **Connect to cloud** (send data to online service)

---

## Useful Resources

- **Arduino IDE**: Download from arduino.cc
- **ESP8266 Guide**: Basic tutorials online
- **Sensor Datasheets**: How to connect each sensor
- **HTML Tutorial**: To improve web interface

---

## Success Checklist

✓ ESP8266 connects to WiFi  
✓ Sensors read data correctly  
✓ Web page shows current data  
✓ Puff detection works  
✓ Data is saved between restarts  
✓ Basic alerts/reminders work  
