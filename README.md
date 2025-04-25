# 🚗 LPC2129 CAN-Based Embedded Dashboard System

A real-time, multi-node **CAN-based dashboard system** built on the **ARM7 LPC2129 microcontroller**. This embedded system simulates a modern vehicle dashboard — complete with **temperature monitoring**, **fuel level display**, **digital clock/calendar**, and **blinking directional indicators** — all beautifully rendered on a **20x4 character LCD**.

---

## ✨ Highlights

✅ Real-Time Clock & Calendar  
🌡️ Temperature Display using DS18B20  
⛽ 5-Level Fuel Gauge Bar on LCD  
🔁 CAN Bus-Based Communication  
⬅️➡️ LCD-Based Left/Right Indicator Blinking  
📟 Custom Characters Using CGRAM  
⚡ External Interrupt-Driven Events

---

## 🧩 System Architecture


- **Main Node (Your Code)** handles:
  - Reading temperature via **DS18B20**
  - Displaying **RTC date & time**
  - Receiving **fuel % over CAN**
  - Displaying left/right arrow based on commands via interrupt or CAN
  - Visual output on **LCD (20x4)**

---

## 🛠️ Hardware Used

| Component        | Description                         |
|------------------|-------------------------------------|
| **LPC2129**      | ARM7 Microcontroller                |
| **DS18B20**      | 1-Wire Digital Temperature Sensor   |
| **MCP2551**      | CAN Transceiver                     |
| **20x4 LCD**     | HD44780-Compatible Character LCD    |
| **RTC (Internal)**| Real-Time Clock for date & time     |
| **Push Buttons** | External interrupts for indicators  |

---

## 🧠 Features Breakdown

### ⏰ Real-Time Clock
- Displays current time, date, and weekday
- Custom display format on LCD

### 🌡️ Temperature Monitor
- Reads ambient temperature via DS18B20
- Displays in real-time with decimal accuracy (e.g., 28.5°C)
- “ND” message when sensor is disconnected

### ⛽ Fuel Gauge (Received via CAN)
- Fuel percentage displayed as both:
  - Numerical value (`85%`)
  - **Graphical bar** using 5-level custom characters

### ⬅️➡️ Direction Indicators
- Left/Right arrows shown as **blinking custom characters**
- Controlled by:
  - **EINT0 (Left)** and **EINT1 (Right)** interrupts
  - **CAN commands** (`'L'` or `'R'`)

---

## 🧪 CAN Protocol Design

| CAN ID | Function              | Data Payload |
|--------|-----------------------|--------------|
| `0x01` | Fuel % Update         | 0–100        |
| `0x02` | Left Indicator Toggle | `'L'`        |
| `0x03` | Right Indicator Toggle| `'R'`        |

---

## 📷 Sample LCD Layout

### 📟 LCD Dashboard Display Snapshot

<div style="width: 20px; margin: auto; background: #f6f8fa; padding: 10px; border-radius: 6px; box-shadow: 0 0 5px rgba(0,0,0,0.1); font-family: monospace;">

<pre>
TIME: 14:23:05      
DATE: 02/04/2025 (Wed)
TEMP: 28.5°C     ⬅️ ➡️
FUEL: █████       85%
</pre>

</div>


---

## 🧰 Code Structure


---

## 🚀 Getting Started

1. 🔌 Connect hardware as per schematic
2. 🧠 Flash firmware to **LPC2129** using Flash Magic or Keil
3. ⚙️ Ensure CAN bus is active with other nodes sending messages
4. 📟 Watch the LCD come to life with real-time updates

---

## 🌟 Future Enhancements

- UART debug output/logging
- Buzzer or warning LED for low fuel/high temp
- Add CAN transmit capability from main node
- Bluetooth module for wireless updates

---

## 👨‍💻 Author

**Anurag Suryawanshi**  
Embedded Systems Developer  
[GitHub](https://github.com/Anuragsurya318) | [LinkedIn](https://linkedin.com/in/anurag-suryawanshi-40a3b420b)

---

## 📝 License

Licensed under the MIT License.  
See `LICENSE` file for details.

---

> 💡 *“Crafting dashboards with code, one CAN frame at a time.”*
