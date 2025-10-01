#include <Arduino.h>
#include <OneButton.h>

#define LED1_PIN 4
#define LED2_PIN 5
#define BUTTON_PIN 35

OneButton button(BUTTON_PIN, true); // true = dùng INPUT_PULLUP

bool ledState = false;      // trạng thái LED
bool blinking = false;      // chế độ nháy
int currentLed = LED1_PIN;  // mặc định điều khiển LED1
unsigned long lastBlink = 0;

void singleClick() {
  blinking = false;
  ledState = !ledState;
  digitalWrite(currentLed, ledState ? HIGH : LOW);
}

void doubleClick() {
  blinking = false;
  // đổi LED được điều khiển
  currentLed = (currentLed == LED1_PIN) ? LED2_PIN : LED1_PIN;
  Serial.print("Đang điều khiển LED trên chân: ");
  Serial.println(currentLed);
}

void longPress() {
  blinking = true;
}

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);

  button.attachClick(singleClick);
  button.attachDoubleClick(doubleClick);
  button.attachLongPressStart(longPress);

  Serial.begin(9600);
}

void loop() {
  button.tick();

  if (blinking) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastBlink >= 200) {
      lastBlink = currentMillis;
      ledState = !ledState;
      digitalWrite(currentLed, ledState ? HIGH : LOW);
    }
  }
}
