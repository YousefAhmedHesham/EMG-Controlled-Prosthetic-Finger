# EMG-Controlled Prosthetic Finger 🦾


## 📌 Project Overview
This project integrates **Electromyography (EMG) signal acquisition** to control a simple prosthetic finger prototype. Developed as part of the **Introduction to Bio-Mechatronics** course at **Ain Shams University**, the system captures muscle signals, processes them via an analog circuit, and uses an embedded microcontroller to drive the finger's motion.

The goal is to demonstrate a feasible approach to prosthetic control using threshold-based logic to switch between gestures.

## 📺 Project Demo
https://github.com/user-attachments/assets/de82bfa0-41c4-4d1c-b832-702a6d393c63

## ⚙️ System Features
### 1. Mechanical Design
* **Rigid Structure:** Unlike cable-driven systems, this design uses rigid mechanical structures to move the finger links.
* **Wearability:** The device is designed to be fixed to the user's hand with a portable electronic box.
* **Degrees of Freedom:** Features at least **1 Actuated DOF** across a minimum of **2 joints**.

### 2. Signal Processing
* **EMG Acquisition:** A custom circuit amplifies and filters raw muscle signals to match the microcontroller's ADC range.
* **Embedded System:** The entire control loop runs on a standalone development board (not dependent on a PC/Laptop).

### 3. Dual Control Modes
The firmware implements two distinct control strategies:
* **Proportional Control (1st Gen):** Maps the **EMG signal envelope amplitude** directly to the finger angle. Stronger muscle contraction = Closed finger; Relaxed muscle = Open finger.
* **Sequential Control (2nd Gen):** Uses a **state diagram** approach. Specific muscle pulses trigger transitions between different fixed gestures or states.

## 🛠 Hardware Architecture
* **Microcontroller:** [e.g., Arduino / ESP32 / Tiva C]
* **Sensors:** Surface EMG Electrodes (Single Channel)
* **Actuators:** [e.g., Servo Motor / DC Motor]
* **Analog Circuit:** Instrumentation Amplifier + Bandpass/Notch Filters

## 🚀 How to Run
1.  **Hardware Setup:** Attach the electrodes to the target muscle group (e.g., forearm).
2.  **Power:** Connect the portable battery pack to the embedded board.
3.  **Mode Selection:** Select between Proportional or Sequential mode.
4.  **Operation:** Flex your muscle to see the rigid links actuate!
