/*********************
 * ESP32 Dual-LED Temperature Alert System
 *
 * Temperature Logic:
 *  - Temp > 24°C        → HIGH  → LED_HIGH ON
 *  - 22°C ≤ Temp ≤ 24°C → LOW   → LED_LOW ON
 *  - Temp < 22°C        → NORMAL → All OFF
 *
 * Display : OLED SSD1306 (128x64)
 * Sensor  : DS18B20
 * Output  : 2 LEDs + Active Buzzer
 *
 * Author  : Milad Mohseni
 *********************/

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* ---------- Pin Definitions ---------- */
#define DS18B20_PIN   4
#define LED_HIGH_PIN  2
#define LED_LOW_PIN   16
#define BUZZER_PIN    15

/* ---------- Temperature Thresholds ---------- */
#define TEMP_LOW_MIN  22.0
#define TEMP_LOW_MAX  24.0

/* ---------- OLED Configuration ---------- */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET   -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* ---------- DS18B20 Setup ---------- */
OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

/* ---------- Buzzer PWM ---------- */
#define BUZZER_ON   240
#define BUZZER_OFF  0

void setup() {
  Serial.begin(115200);

  pinMode(LED_HIGH_PIN, OUTPUT);
  pinMode(LED_LOW_PIN, OUTPUT);

  digitalWrite(LED_HIGH_PIN, LOW);
  digitalWrite(LED_LOW_PIN, LOW);

  ledcAttach(BUZZER_PIN, 2000, 8);
  ledcWrite(BUZZER_PIN, BUZZER_OFF);

  sensors.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  Serial.print("Temperature: ");
  Serial.println(temperature);

  display.clearDisplay();

  /* ---------- Temperature Display ---------- */
  display.setTextSize(3);
  display.setCursor(0, 0);
  display.print(temperature, 1);
  display.print("C");

  display.setTextSize(2);
  display.setCursor(0, 40);

  /* ---------- State Logic ---------- */
  if (temperature > TEMP_LOW_MAX) {
    // HIGH
    display.print("HIGH");

    digitalWrite(LED_HIGH_PIN, HIGH);
    digitalWrite(LED_LOW_PIN, LOW);
    ledcWrite(BUZZER_PIN, BUZZER_ON);
  }
  else if (temperature >= TEMP_LOW_MIN && temperature <= TEMP_LOW_MAX) {
    // LOW
    display.print("LOW");

    digitalWrite(LED_HIGH_PIN, LOW);
    digitalWrite(LED_LOW_PIN, HIGH);
    ledcWrite(BUZZER_PIN, BUZZER_ON);
  }
  else {
    // NORMAL
    display.print("NORMAL");

    digitalWrite(LED_HIGH_PIN, LOW);
    digitalWrite(LED_LOW_PIN, LOW);
    ledcWrite(BUZZER_PIN, BUZZER_OFF);
  }

  display.display();
  delay(1000);
}