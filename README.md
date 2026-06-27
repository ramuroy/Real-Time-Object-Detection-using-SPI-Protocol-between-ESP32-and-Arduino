# SPI-Based Object Detection using ESP32 & Arduino 🚀🎯

![ESP32](https://img.shields.io/badge/ESP32-Master-E7352C?style=flat-square&logo=espressif&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-Slave-00979D?style=flat-square&logo=arduino&logoColor=white)
![SPI](https://img.shields.io/badge/Protocol-SPI-660066?style=flat-square)
![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-3da639?style=flat-square)

## Project Overview

This project demonstrates an **SPI-based communication system** between an **ESP32 (Master)** and an **Arduino (Slave)** for **object detection** using an **IR sensor**. The **ESP32** acts as the master device, sending a message to the **Arduino**, which outputs it to the **Serial Monitor**.

## Key Features

- **Master-Slave SPI Communication** between **ESP32** and **Arduino** 🔄
- **IR Sensor** for detecting objects and triggering the communication process 🛸
- **Edge-triggered detection** — one message per detection event, not a flood ⏱️
- **Interrupt-driven slave** (`SPI_STC_vect`) with a bounds-checked receive buffer 🛡️
- **Serial Monitor Output** on Arduino to display the results 💻

## How It Works

1. **IR Sensor Detection**: the **IR sensor** detects an object, pulling the ESP32 input LOW.
2. **SPI Communication**: on the new-detection edge, the **ESP32** sends one timestamped, newline-terminated message to the **Arduino (Slave)** over SPI 🔗.
3. **Serial Monitor**: the **Arduino** receives each byte in its SPI interrupt, reassembles the message, and prints it to the **Serial Monitor** 📡.

## Components Used

- **ESP32** (Master) 🌍
- **Arduino Uno** (Slave) 🤖
- **IR Sensor** 🔍
- Connecting Wires 🔌
- Breadboard (optional) 🧑‍🔬

## How to Run

### 1. Wiring

The Arduino Uno's SPI pins are fixed; the ESP32 uses the custom pins defined in the sketch:

| Signal | ESP32 (Master) | Arduino Uno (Slave) |
|--------|:--------------:|:-------------------:|
| SCK    | GPIO 26 | D13 |
| MOSI   | GPIO 33 | D11 |
| MISO   | GPIO 25 | D12 |
| SS / CS | GPIO 5 | D10 |
| GND    | GND | GND |

- **IR sensor** → ESP32 **GPIO 35** &nbsp;•&nbsp; detection **LED** → ESP32 **GPIO 27**

> ⚠️ **Logic levels:** the ESP32 is 3.3 V and the Uno is 5 V. The master only drives SCK/MOSI/SS into the Uno (3.3 V is read as a valid HIGH), and MISO is unused in this one-way demo, so a direct connection works for a quick test — but for a robust build add a level shifter on those lines.

### 2. Upload the Code

- Upload `Mastercode-ESP32.ino` to the **ESP32** and `Slave-Arduino.ino` to the **Arduino Uno**, each from its own sketch in the Arduino IDE.
- Open the **Serial Monitor** on the Arduino (115200 baud) to see the output.

### 3. Observe the Results

- When an object is detected by the **IR sensor**, the **ESP32** sends a single message and the Arduino prints the detection result to the **Serial Monitor**.

## Demo

Check out the demonstration video of the project in action:  
🔗 [Click here to watch the demonstration on LinkedIn](https://www.linkedin.com/posts/ramu-roy-b780382b7_embeddedsystems-spicommunication-esp32-activity-7303300003546996736-tI5h?utm_source=social_share_send&utm_medium=android_app&rcm=ACoAAEwAX4wBY70YZ3l58lvkiXtyCZcnWWrfJAA&utm_campaign=copy_link)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Thanks to the creators of the **ESP32** and **Arduino** platforms.
- Special thanks to the community for their contributions to the **SPI protocol** and **IR sensors**.
