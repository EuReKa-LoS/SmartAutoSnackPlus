#include "leds.h"

void initLeds() {
  pinMode(PIN_LED_ROUGE, OUTPUT);
  pinMode(PIN_LED_BLEU, OUTPUT);
  pinMode(PIN_LED_VERT, OUTPUT);

  digitalWrite(PIN_LED_ROUGE, LOW);
  digitalWrite(PIN_LED_BLEU, LOW);
  digitalWrite(PIN_LED_VERT, LOW);
}

void updateLeds(const SystemStatus &status) {
  // LED Rouge : niveau croquettes critique ou erreur
  digitalWrite(PIN_LED_ROUGE, (status.niveauCroquette == CROQ_CRITIQUE) ? HIGH : LOW);

  // LED Bleu : clignote si pas connecté au WiFi
  static unsigned long previousMillis = 0;
  static bool ledState = LOW;
  unsigned long currentMillis = millis();

  if (!status.wifiConnected) {
    if (currentMillis - previousMillis >= 500) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(PIN_LED_BLEU, ledState);
    }
  } else {
    digitalWrite(PIN_LED_BLEU, LOW);
  }

  // LED Verte : allumée en mode reset
  digitalWrite(PIN_LED_VERT, status.inResetMode ? HIGH : LOW);
}

void testLeds() {
  digitalWrite(PIN_LED_ROUGE, HIGH);
  delay(1000);
  digitalWrite(PIN_LED_ROUGE, LOW);

  digitalWrite(PIN_LED_BLEU, HIGH);
  delay(1000);
  digitalWrite(PIN_LED_BLEU, LOW);

  digitalWrite(PIN_LED_VERT, HIGH);
  delay(1000);
  digitalWrite(PIN_LED_VERT, LOW);
}
