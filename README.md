# 🔵 COSMO EYES
### A Mini Animated Robot Companion

**An embedded systems project combining OLED animation, touch interaction, and a compact transparent hardware enclosure.**

COSMO EYES is a miniature interactive robot-face project built around an ESP32-C3 Super Mini and an OLED display. It brings a tiny electronic companion to life through expressive cyan eyes, blinking animations, and touch-controlled facial expressions.

The project explores how microcontroller programming and simple display graphics can transform a small electronic device into an interactive character.

---

## ✨ Features

- 🔹 Animated cyan-style robot eyes
- 👀 Multiple facial expressions
- 😊 Normal, Happy, Angry, and Sleepy eye modes
- 😉 Automatic blinking and idle eye movement
- 👆 Touch-controlled expression switching
- ⚡ Real-time animation using non-blocking timing
- 🧩 Compact transparent enclosure
- 🔌 USB access for programming and power, depending on the hardware configuration

---

## 📸 Hardware Prototype

The current prototype combines a small OLED display and electronic components inside a transparent enclosure, creating a compact, portable robot companion.

The enclosure allows the electronics to remain visible while protecting the assembly.

**Prototype highlights**
- Small-form-factor construction
- Custom animated OLED interface
- Transparent protective casing
- Integrated electronic hardware
- Touch-responsive interaction

> Add your actual prototype photographs here to showcase the assembled device and its expressions.

---

## 🛠️ Hardware Components

| Component | Purpose |
|---|---|
| ESP32-C3 Super Mini | Microcontroller and animation control |
| SSD1306 OLED display | Displays the robot eyes |
| Capacitive touch sensor | User interaction and expression changes |
| USB connection | Programming and power, depending on the board |
| Transparent enclosure | Protects and houses the electronics |
| Connecting wires | Electrical interconnections |

*The exact board variant, touch-sensor module, and battery or power circuitry should be documented after verification.*

---

## 🔌 Pin Configuration

The current firmware uses the following pin assignments.

| Signal | ESP32-C3 GPIO |
|---|---|
| OLED SDA | GPIO 8 |
| OLED SCL | GPIO 9 |
| Touch sensor output | GPIO 4 |

The OLED communicates with the microcontroller over I²C.

Verify the physical wiring and module voltage requirements before connecting the hardware.

---

## 👁️ Eye Expressions

| Mode | Visual behaviour |
|---|---|
| Normal | Rounded eyes with gentle movement |
| Happy | Wider, shorter eyes |
| Angry | Narrow eyes with angled eyelids |
| Sleepy | Drooping eyelids and relaxed movement |

A touch advances the display to the next expression.

The OLED is monochrome, so the cyan appearance depends on the display module itself.

---

## ⚙️ System Architecture

The project consists of three main functional blocks:

1. **Input:** The touch sensor detects user interaction.
2. **Processing:** The ESP32-C3 manages expression states and animation timing.
3. **Output:** The OLED renders the eye graphics and animations.

The firmware uses a state-based approach to switch expressions and update the display.

Animation timing uses `millis()` to reduce dependence on long blocking delays, keeping the main loop responsive to touch events.

---

## 💻 Software and Tools

- Arduino IDE
- Arduino C++
- ESP32 board support package
- Adafruit GFX Library
- Adafruit SSD1306 Library
- I²C communication

---

## 🚀 Getting Started

1. Install Arduino IDE.
2. Install the ESP32 board support package.
3. Install the Adafruit GFX and Adafruit SSD1306 libraries.
4. Connect the OLED and touch sensor using the verified pin configuration.
5. Open the firmware sketch.
6. Select the appropriate ESP32-C3 board and serial port.
7. Compile and upload the firmware.
8. Touch the sensor to cycle through the expressions.

---

## 🧠 Engineering Concepts Demonstrated

- Embedded C++ programming
- GPIO input handling
- I²C peripheral communication
- OLED graphics rendering
- State-based firmware design
- Touch-event detection and debounce
- Non-blocking timing with `millis()`
- Hardware and firmware integration
- Compact electronic product prototyping

---

## 🔮 Future Improvements

- Smoother eye transitions and eyelid animations
- Additional expressions and interaction patterns
- Improved enclosure finishing and internal mounting
- Verified rechargeable battery integration
- Low-power idle and sleep modes
- A short animation demo and complete wiring diagram
- Improved documentation and reproducible hardware assembly

---

## 🎯 Project Objective

The goal of COSMO EYES is to develop a compact interactive electronic companion while gaining practical experience in embedded firmware, display interfacing, and hardware prototyping.

It is also an exploration of how expressive interfaces can make small electronic devices feel more engaging.

---

## 👩‍💻 Developer

**Vinu**  
Electronic Engineering | Embedded Systems | Microcontrollers

---

*Built with code, curiosity, and a little robot personality.* 🤖

