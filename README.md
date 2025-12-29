# ESP32-Temperature-Alarm-System
ESP32-based temperature monitoring and alert system using DS18B20, OLED display, dual LED indicators, and buzzer with threshold-based logic.


# ESP32 Temperature Alarm System

An ESP32-based real-time temperature monitoring and alert system using a DS18B20 sensor, OLED display, dual LED indicators, and an active buzzer.

## Features
- Real-time temperature measurement
- Threshold-based alert logic
- Dual LED indication for LOW and HIGH temperature states
- Audible buzzer alert
- Large, readable OLED output
- Designed with real-world behavior in mind

## Temperature Logic
| Temperature Range | Status | LED_HIGH | LED_LOW | Buzzer |
|------------------|--------|----------|---------|--------|
| > 24°C           | HIGH   | ON       | OFF     | ON     |
| 22°C – 24°C      | LOW    | OFF      | ON      | ON     |
| < 22°C           | NORMAL | OFF      | OFF     | OFF    |

## Hardware Components
- ESP32 Development Board
- DS18B20 Temperature Sensor
- OLED Display (SSD1306, 128x64)
- 2 × LEDs (with 220Ω resistors)
- Active Buzzer
- Breadboard & Jumper Wires

## Pin Configuration
| Component | ESP32 Pin |
|---------|-----------|
| DS18B20 Data | GPIO4 |
| LED_HIGH | GPIO2 |
| LED_LOW | GPIO16 |
| Buzzer | GPIO15 |
| OLED SDA | GPIO21 |
| OLED SCL | GPIO22 |

## Wiring
See wiring diagram in the images/ folder.

## How It Works
1. ESP32 reads temperature from DS18B20 sensor.
2. Temperature is compared against predefined thresholds.
3. System state is determined (NORMAL / LOW / HIGH).
4. LEDs, buzzer, and OLED display respond accordingly.
5. System updates every second.

## Demo
A short demonstration video is available in the video/ folder showing:
- Normal state
- Low temperature alert
- High temperature alert

## Libraries Used
- OneWire
- DallasTemperature
- Adafruit_GFX
- Adafruit_SSD1306

## Author
*Milad Mohseni*

## License
MIT License
