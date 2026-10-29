#include <AETHER_MK-1_inferencing.h>
#include <WiFi.h>

// ======================================================
// AETHER MK-1: NON-INVASIVE HUMAN DETECTION RADAR
// NEURAL NETWORK INFERENCE ENGINE (MASTER BRANCH)
// ======================================================

#define TARGET_SSID "AETHER_TX_MK-1"

const int RED_ALERT_LED = 4;  // GPIO4

float features[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE];
int feature_ix = 0;

void setup() {
  Serial.begin(115200);

  pinMode(RED_ALERT_LED, OUTPUT);
  digitalWrite(RED_ALERT_LED, LOW);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("\n[SYSTEM] AETHER MK-1 BOOT SEQUENCE INITIATED...");

  WiFi.begin(TARGET_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n[SYSTEM] RADAR LOCK ACQUIRED!");
  Serial.println("[SYSTEM] Neural Network Running...");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    int current_rssi = WiFi.RSSI();
    features[feature_ix++] = current_rssi;

    if (feature_ix == EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE) {
      signal_t signal;
      numpy::signal_from_buffer(
        features, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);

      ei_impulse_result_t result = { 0 };
      run_classifier(&signal, &result, false);

      Serial.println("\n=== AETHER MK-1 RADAR SCAN ===");

      bool human_detected = false;

      for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        Serial.print("TARGET [");
        Serial.print(result.classification[ix].label);
        Serial.print("] CONFIDENCE: ");
        Serial.print(result.classification[ix].value * 100.0);
        Serial.println("%");

        if (strcmp(result.classification[ix].label, "struggle") == 0
            && result.classification[ix].value > 0.60) {
          human_detected = true;
        }
      }

      if (human_detected) {
        Serial.println(">> RED ALERT: HUMAN MOVEMENT DETECTED! <<");
        digitalWrite(RED_ALERT_LED, HIGH);
      } else {
        digitalWrite(RED_ALERT_LED, LOW);
      }

      feature_ix = 0;
    }
  } else {
    Serial.println("[ERROR] Hard Lock Lost! Re-engaging...");
    digitalWrite(RED_ALERT_LED, LOW);
    WiFi.disconnect();
    WiFi.begin(TARGET_SSID);
    delay(1000);
  }

  delay(8);  // Match 8ms training data collection rate
}
