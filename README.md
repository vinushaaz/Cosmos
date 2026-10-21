# 🔵 COSMO EYES | Animated OLED Robot Companion

**A tiny robot with expressive eyes, built with embedded systems.**

COSMO EYES is a mini interactive robot-eye project developed using an ESP32-C3 Super Mini, an SSD1306 OLED display, and a touch sensor. It brings a simple display to life through animated eye movements, blinking, and touch-controlled expressions.

The goal is to combine embedded programming, display graphics, hardware interfacing, and interactive design into a compact project.

## ✨ Features

- Animated cyan-style robot eyes on a dark OLED background
- Four touch-controlled expressions: Normal, Happy, Angry, and Sleepy
- Automatic blinking animation
- Eye movement to create a lively idle state
- Touch sensor input for user interaction
- Non-blocking animation timing using `millis()`
- Compact design suitable for a mini robot or keychain concept

## 🛠️ Hardware Components

| Component | Purpose |
|---|---|
| ESP32-C3 Super Mini | Main microcontroller |
| SSD1306 128×64 OLED | Displays the animated eyes |
| Capacitive touch sensor | Changes the eye expression |
| Jumper wires | Hardware connections |
| USB cable | Programming and power during development |

## 🔌 Pin Connections

| Signal | ESP32-C3 Pin |
|---|---|
| OLED SDA | GPIO 8 |
| OLED SCL | GPIO 9 |
| Touch sensor OUT | GPIO 4 |
| OLED VCC | According to module specifications |
| OLED GND | GND |
| Touch sensor GND | GND |

**Note:** The pin assignments are based on the current firmware configuration. Verify the actual module pinouts and voltage requirements before connecting the hardware.

## 👀 Eye Expressions

| Expression | Behaviour |
|---|---|
| Normal | Rounded eyes with idle movement |
| Happy | Wider, shorter eyes |
| Angry | Narrow eyes with angled eyelids |
| Sleepy | Drooping eyelids and gentle movement |

Touch the sensor to cycle through the expressions.

## ⚙️ How It Works

1. The ESP32-C3 initializes the OLED over I²C.
2. The firmware draws the eye shapes using the Adafruit GFX and SSD1306 libraries.
3. The main loop checks for a new touch event.
4. Each valid touch advances the expression state.
5. The animation loop updates eye positions and blinking using `millis()`.

This approach keeps the display animation and touch interaction responsive without relying on long delays.

## 💻 Software Requirements

- Arduino IDE
- ESP32 board support package
- Adafruit GFX Library
- Adafruit SSD1306 Library

## 🚀 Getting Started

1. Install the required libraries in Arduino IDE.
2. Open `cosmo_eyes.ino`.
3. Select the appropriate ESP32-C3 board and port.
4. Verify the OLED and touch sensor wiring.
5. Upload the firmware.
6. Touch the sensor to explore the different expressions.

## 🧠 Engineering Concepts Applied

- Microcontroller programming using Arduino C++
- I²C communication
- GPIO input handling
- Event detection and debounce logic
- State-based interaction
- Frame-based display animation
- Non-blocking timing with `millis()`
- Embedded hardware and software integration

## 🔮 Future Improvements

- Smoother transitions between expressions
- More expressive eye shapes and animations
- Rechargeable battery operation
- Compact transparent acrylic enclosure
- Low-power idle mode
- Additional touch gestures and interaction patterns

## 🎯 Project Goal

To build a compact, interactive electronic companion while developing practical skills in embedded firmware, hardware interfacing, and real-time display animation.

## 👩‍💻 Developer

**Vinu**

Electronic Engineering | Embedded Systems | Microcontrollers

---

*Built with curiosity, code, and a little bit of robot personality.* 🤖
