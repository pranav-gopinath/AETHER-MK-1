<div align="center">
  <img src="assets/zeniq_logo.png" alt="ZENIQ Team Logo" width="500" />
  <h1>AETHER MK-1</h1>
  <p><strong>Ambient Edge-Computing Topology for Non-Line-Of-Sight Human Emergency Rescue</strong></p>

  <!-- GitHub badges -->
  <img src="https://img.shields.io/badge/Hardware-ESP32-blue?style=for-the-badge&logo=espressif" alt="ESP32" />
  <img src="https://img.shields.io/badge/AI-TinyML-orange?style=for-the-badge" alt="TinyML" />
  <img src="https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B" alt="C++" />
  <img src="https://img.shields.io/badge/Budget-<%20₹1,000-brightgreen?style=for-the-badge" alt="Budget" />
</div>

<br />

<!-- GIF PLACEHOLDER -->
<div align="center">
<img width="540" height="304" alt="presentation_video" src="https://github.com/user-attachments/assets/57d81741-fec4-448f-8a5d-f0a8b73b82ab" />
</div>

## The Mission

During structural collapses, the critical window to locate trapped survivors is 72 hours. Traditional Search and Rescue (SAR) technologies face severe physical limitations: thermal cameras cannot penetrate solid concrete, rescue dogs are impeded by toxic hazards, and acoustic microphones require the victim to be conscious. 

**AETHER MK-1** bypasses these limitations. Operating entirely via edge computing, it is an ultra-low-cost, non-line-of-sight radar system that utilizes standard 2.4GHz Wi-Fi signals to detect the physical movements of trapped bodies through solid barriers.

**Project Origins:** This system was conceived and developed as a first-year college engineering project. I served as the Team Leader for **Team ZENIQ**, driving the core hardware architecture, machine learning pipeline, and field testing to ensure the project met strict budget and performance constraints.

## Core Architecture
The system is built on a two-node hardware architecture using commodity DOIT ESP32 DevKit V1 microcontrollers, keeping the total deployment cost under ₹1,000 per node.

* **Transmitter Node (Illuminator):** Configured as an Access Point (SSID: `AETHER_TX_MK-1`), it continuously floods the debris field with 2.4GHz electromagnetic radiation.
* **Receiver Node (AI Brain & Radar):** Maintains a "Hard Lock" to the Illuminator to prevent signal dropout. It polls the Received Signal Strength Indicator (RSSI) every 8 milliseconds.
* **Alert Mechanism:** A physical GPIO-driven visual alert triggers instantly upon a positive AI classification, requiring zero graphical user interfaces or cloud connectivity.

## Machine Learning Pipeline
AETHER relies on a TinyML binary classifier trained to differentiate between dead rubble and active human movement. 

1. **Data Acquisition:** The system captures multipath interference caused by RF scattering. Raw RSSI telemetry was logged via a custom Python script into `real_idle.csv` and `real_struggle.csv` datasets.
2. **Feature Extraction:** Time-series data is aggregated into a 125-sample memory buffer, representing one second of physical environment analysis.
3. **Offline Inference:** The raw RSSI data undergoes Digital Signal Processing (DSP) and is fed into a quantized neural network optimized via Edge Impulse. 
4. **Classification:** If the dynamic movement confidence interval exceeds 60%, the C++ inference engine flags a human detection event.

## Performance & Testing
* **Static Control (Empty Room):** Maintained a 91.3% "idle" confidence, successfully ignoring ambient baseline noise.
* **Dynamic Target (Behind Wall):** Human movement behind an opaque barrier triggered an 87.2% "struggle" classification.
* **Micro-Movement:** Small-scale movement behind dense structural material registered 79.8% detection confidence, instantly triggering the physical GPIO alert.

## Future Scope (MK-2 Roadmap)
While MK-1 successfully proves the physics of RSSI-based RF detection, it requires active physical movement. The AETHER MK-2 development roadmap targets unconscious survivors by transitioning from RSSI to **Channel State Information (CSI)** phase-shift extraction. CSI provides subcarrier-level hyper-sensitivity capable of detecting the millimeter-level expansion of a human chest cavity during breathing.
