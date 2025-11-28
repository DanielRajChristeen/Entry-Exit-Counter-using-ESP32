# 📘 **Entry–Exit Counter using ESP32**

A simple yet powerful mini-project built using the **ESP32 DevKit**, combining an **IR Sensor**, **Ultrasonic Sensor (HC-SR04)**, and a **7-segment display** to count entries and exits in real time.

This project is part of my **2-week ESP32 internship learning journey**, where I focused on understanding real-world sensor behavior, GPIO handling, and building reliable state-based logic on embedded systems.

---

## 🚀 Features

* **IR Sensor → count++** (entry detection)
* **Ultrasonic Sensor → count--** (exit detection)
* **7-Segment Display** shows real-time count
* **Debounced rising-edge logic** for IR sensor
* **Noise-filtered ultrasonic detection**
* **Latch system** prevents multiple decrement counts
* Clean, stable, and optimized for ESP32 GPIO behavior

---

## 🧩 Hardware Used

* ESP32 DevKit V1
* IR Obstacle Sensor
* HC-SR04 Ultrasonic Sensor
* Single-digit 7-segment display (common cathode)
* Jumper wires
* Breadboard

---

## **Pin Connections**

| Component               | ESP32 Pin                |
| ----------------------- | ------------------------ |
| IR Sensor OUT           | GPIO 14                  |
| Ultrasonic TRIG         | GPIO 4                   |
| Ultrasonic ECHO         | GPIO 16                  |
| 7-Segment a,b,c,d,e,f,g | GPIO 23,22,21,19,18,5,17 |

---

## 📜 Full Algorithm

### **1️⃣ Entry Counting – IR Sensor (count++)**

* Read IR sensor continuously
* Detect *rising edge* (0 → 1 transition)
* Increment count
* Update 7-segment display

### **2️⃣ Exit Counting – Ultrasonic Sensor (count--)**

Ultrasonic values are noisy, so filtered using stability windows:

* Measure distance repeatedly
* If **distance is 2–8 cm** for **3 consecutive readings** → obstacle detected
* If **distance > 9 cm** for **5 consecutive readings** → obstacle cleared
* Decrement the count **only once per detection cycle** (using latch logic)
* Update display

### **3️⃣ 7-Segment Display**

* Maps single-digit output (0–9)
* Displays updated count every time a sensor triggers

### **4️⃣ System Behavior**

* No double-counting
* No false triggers
* Smooth loop for stable detection

---

## 🛠 How to Run

1. Install **Arduino IDE**
2. Add the ESP32 board manager URL
3. Select:

   * Board: *ESP32 DevKit V1*
   * Port: *Your COM port*
4. Upload the code
5. Keep IR & Ultrasonic sensors facing clear directions
6. Watch count update on 7-segment display

---

## 🧪 Demo Output (Serial Monitor Sample)

```
IR detected → Count: 1
Ultrasonic detected EXIT → Count: 0
```

---

## 🌱 Learnings from the Project

* Handling real-world sensor noise
* Designing detection windows & stability checks
* Pin conflict resolution on ESP32
* Practical state machine implementation
* Building reliable embedded logic
* Debugging ultrasonic anomalies & edge cases

---
