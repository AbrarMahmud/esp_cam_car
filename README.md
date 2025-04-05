# 📷 WiFi-RoverCam: ESP32-CAM Controlled RC Vehicle Over Local WiFi

This project demonstrates a standalone **WiFi-based RC vehicle system** using the **ESP32-CAM module**. It serves a custom HTML-based camera interface over a local HTTP server without requiring internet access. The vehicle is controlled via a custom web page, and the control signals are relayed wirelessly to an Arduino Uno handling motor control.

<div align="center">
  <img src="https://github.com/AbrarMahmud/esp_cam_car/blob/master/source%20code/IMG_0492.gif" alt="github-small" width="60%">
</div>

## 🚀 Project Overview

**WiFi-RoverCam** transforms an RC vehicle into a camera-equipped smart rover that operates over local WiFi. Users can access a live video stream and control the rover using a browser on any device connected to the ESP32-CAM's WiFi hotspot.

### 🔧 Key Features:
- ESP32-CAM serves as a standalone HTTP server
- Embedded HTML+JavaScript interface for camera and control
- Wireless rover movement using ESP32-CAM → Arduino Uno (via virtual serial)
- No internet connection required — local WiFi hotspot-based control
- Compressed HTML interface embedded in firmware

---

## 📁 File Structure

```plaintext
WiFi-RoverCam/
│
├── drive_control_ard_uno/
│   └── drive_control_ard_uno.ino     # Arduino code to control motor driver using serial input
│
├── esp32_cam_customWeb_car/
│   ├── esp32_cam_customWeb_car.ino  # Main ESP32-CAM sketch (HTTP server + camera init)
│   └── camera_index.h               # Contains encoded HTML UI in gzip-compressed byte array
```

---

## 🔌 Hardware Requirements

- ESP32-CAM Module
- Arduino Uno (or compatible board)
- Motor Driver (L298N or similar)
- Dual/4-Wheel Chassis with DC motors
- Power Supply (LiPo or regulated 5V)
- Jumper Wires

---

## 🌐 How It Works

1. **ESP32-CAM acts as a local WiFi hotspot**. It broadcasts an HTTP link that users can connect to from any WiFi-enabled device.
2. **HTML UI** is served from ESP32-CAM’s flash memory. The UI includes controls and a live video stream.
3. **User input** (directional control) from the web page is received by ESP32-CAM and sent over UART to the Arduino Uno.
4. **Arduino Uno** decodes the serial commands and controls the motors via an H-bridge motor driver.

---

## 📦 Encoding HTML for ESP32-CAM (camera_index.h)

To embed a rich web interface into the ESP32-CAM firmware, the raw `.html` file is first compressed and encoded into a C-style byte array. Here's how it was done:

### ✅ Steps:

1. **Write your custom HTML + JavaScript page.** This is your UI for controlling the car and viewing the camera stream.
2. **Use CyberChef (https://gchq.github.io/CyberChef/)** with the following recipe:
   - **Gzip Compression** – compress your `.html` file.
   - **Convert to Hex Dump or Byte Array** – for embedding into Arduino code.
   - (Optional) **Dynamic Huffman Coding** – used to further reduce the file size and make it compatible with browser decompression mechanisms.
3. **Save the encoded output** as `camera_index.h`, and include it in your ESP32 project.


This method optimizes memory usage on the ESP32 and allows serving a fast, compressed web UI.

---

## 🛠️ Getting Started

### 🖥️ Arduino IDE Setup:

1. Install **ESP32 board support** via Board Manager.
2. Install the following libraries (if needed):
   - `ESPAsyncWebServer`
   - `AsyncTCP`
   - `FS`, `SPIFFS`, etc.

### 📲 Upload Instructions:

1. Connect ESP32-CAM using USB-to-Serial (with GPIO 0 pulled LOW).
2. Upload `esp32_cam_customWeb_car.ino`.
3. Upload `drive_control_ard_uno.ino` to Arduino Uno.
4. Power both boards and connect to the ESP32-CAM's WiFi.
5. Open browser → type the IP shown in Serial Monitor.

---

## 🧪 Demo

📷 **Live Camera Stream**  
🎮 **Control Buttons (Forward, Back, Left, Right)**  
🔌 **Works entirely offline — great for robotics & surveillance**

---

## 🧠 Future Improvements

- Add real-time obstacle detection with ultrasonic sensors
- Integrate voice control or gesture recognition
- Add MQTT or Bluetooth fallback for control
- Use WebSockets for faster response instead of polling

---

## 📜 License

MIT License

---

## 🤝 Contributions

PRs and suggestions are welcome! Please open issues for bugs or feature requests.

---

## 🔗 Credits

- [CyberChef – GCHQ](https://gchq.github.io/CyberChef/)
- Arduino & ESP32 community examples
