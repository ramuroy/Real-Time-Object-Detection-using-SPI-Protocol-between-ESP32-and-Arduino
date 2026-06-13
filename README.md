# SPI-Based Object Detection using ESP32 & Arduino 🚀🎯

![ESP32](https://img.shields.io/badge/ESP32-Master-E7352C?style=flat-square&logo=espressif&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-Slave-00979D?style=flat-square&logo=arduino&logoColor=white)
![SPI](https://img.shields.io/badge/Protocol-SPI-660066?style=flat-square)
![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-3da639?style=flat-square)

## Project Overview

This project demonstrates an **SPI-based communication system** between an **ESP32 (Master)** and an **Arduino (Slave)** for **object detection** using an **IR sensor**. The **ESP32** acts as the master device, sending signals to the **Arduino**, which outputs relevant messages to the **Serial Monitor**.

## Key Features

- **Master-Slave SPI Communication** between **ESP32** and **Arduino** 🔄
- **IR Sensor** for detecting objects and triggering the communication process 🛸
- **Real-Time Object Detection** where detected objects are communicated via SPI ⏱️
- **Serial Monitor Output** on Arduino to display the results 💻

## How It Works

1. **IR Sensor Detection**: The **IR sensor** detects an object and sends a signal to the **ESP32 (Master)**.
2. **SPI Communication**: The **ESP32** sends the signal to the **Arduino (Slave)** via the **SPI protocol** 🔗.
3. **Serial Monitor**: The **Arduino (Slave)** receives the data and outputs a message to the **Serial Monitor**, indicating the object detection status 📡.

## Components Used

- **ESP32** (Master) 🌍
- **Arduino** (Slave) 🤖
- **IR Sensor** 🔍
- Connecting Wires 🔌
- Breadboard (optional) 🧑‍🔬

## How to Run

### 1. Setup

- Connect the **IR sensor** to the **ESP32** as per the wiring diagram.
- Connect the **ESP32** and **Arduino** using the SPI pins:  
  - **MOSI** (ESP32) to **MOSI** (Arduino)  
  - **MISO** (ESP32) to **MISO** (Arduino)  
  - **SCK** (ESP32) to **SCK** (Arduino)  
  - **CS** (ESP32) to **SS** (Arduino)

### 2. Upload the Code

- Upload the code to the **ESP32** and **Arduino** from the respective IDEs (Arduino IDE for Arduino, ESP32 compatible IDE for ESP32).
- Open the **Serial Monitor** on the **Arduino IDE** to see the output.

### 3. Observe the Results

- When an object is detected by the **IR sensor**, the **ESP32** will send a signal to the **Arduino**, and the Arduino will print the detection result to the **Serial Monitor**.

## Demo

Check out the demonstration video of the project in action:  
🔗 [Click here to watch the demonstration on LinkedIn](https://www.linkedin.com/posts/ramu-roy-b780382b7_embeddedsystems-spicommunication-esp32-activity-7303300003546996736-tI5h?utm_source=social_share_send&utm_medium=android_app&rcm=ACoAAEwAX4wBY70YZ3l58lvkiXtyCZcnWWrfJAA&utm_campaign=copy_link)


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

- Thanks to the creators of the **ESP32** and **Arduino** platforms.
- Special thanks to the community for their contributions to the **SPI protocol** and **IR sensors**.
