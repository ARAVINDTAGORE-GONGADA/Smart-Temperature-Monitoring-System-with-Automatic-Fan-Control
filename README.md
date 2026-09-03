# Smart Temperature Monitoring System with Automatic Fan Control

A temperature-controlled cooling system built with an **Arduino Uno**, a **TMP36 analog temperature sensor**, and a **DC motor (fan)** driven through an **NPN transistor**. The motor's speed increases proportionally with temperature, simulated and tested in **Tinkercad Circuits**.

---

## Project Overview

This project reads ambient temperature using a TMP36 analog sensor and automatically controls the speed of a DC motor (acting as a cooling fan) using PWM. As the temperature rises, the fan spins faster; below a set threshold, the fan stays off. The Arduino also logs live temperature and PWM readings to the Serial Monitor for observation.

## Objective

- Read analog temperature data from a TMP36 sensor.
- Convert the raw sensor voltage into a temperature value (°C).
- Drive a DC motor at a speed proportional to temperature using PWM.
- Provide real-time feedback via the Serial Monitor.

## Components Used

| Component | Quantity | Purpose |
|---|---|---|
| Arduino Uno | 1 | Microcontroller / main board |
| TMP36 Temperature Sensor | 1 | Measures ambient temperature |
| NPN Transistor | 1 | Switches/drives the motor using a PWM signal from the Arduino |
| Resistor | 1 | Current-limiting resistor on the transistor base |
| DC Motor (gear motor) | 1 | Acts as the cooling fan / output actuator |
| Breadboard | 1 | Prototyping the circuit |
| Jumper wires | Several | Circuit connections |
| USB cable | 1 | Power and programming |

## Software / Tools Used

- **Arduino IDE** – writing and uploading the `.ino` sketch
- **Tinkercad Circuits** – circuit design and simulation (no physical hardware was required for testing)
- **GitHub** – version control and project hosting

## Circuit Description

The circuit was designed and simulated in Tinkercad. It consists of:

- A **TMP36 sensor** with its signal pin connected to Arduino analog pin **A0**, and its power/ground pins connected to the breadboard's 5V and GND rails.
- An **NPN transistor** used as a low-side switch to drive the DC motor. Its base is connected (through a resistor) to Arduino digital pin **9**, which outputs a PWM signal. The transistor's collector/emitter path controls current flow through the motor.
- A **DC gear motor**, powered from the 5V rail through the transistor, acting as the fan/output device whose speed is controlled by the PWM duty cycle.
- The Arduino's **5V** and **GND** pins are connected to the breadboard's power rails via red and black jumper wires to power the sensor and motor circuit.

*See `images/circuit_diagram.png` for the full Tinkercad circuit layout.*

## Pin Connections

| Arduino Pin | Connected To | Wire Color (in Tinkercad) |
|---|---|---|
| A0 | TMP36 signal (output) pin | Blue |
| Digital Pin 9 (PWM) | Transistor base (via resistor) | Yellow |
| 5V | Breadboard positive (+) rail | Red |
| GND | Breadboard negative (–) rail | Black |

> The TMP36's power and ground legs, along with the motor and transistor, are wired to the breadboard's shared power rails rather than directly to the Arduino.

## Working Principle

1. The Arduino continuously reads the analog voltage from the TMP36 sensor on pin **A0**.
2. This raw ADC value (0–1023) is converted into an actual voltage:
   `voltage = sensorValue * (5.0 / 1023.0)`
3. The voltage is converted into a temperature in °C using the TMP36's linear formula:
   `temperature = (voltage - 0.5) * 100.0`
4. The temperature is mapped to a PWM value (0–255) sent to the motor:
   - Below **27°C** → PWM = 0 (motor off)
   - Between **27°C and 40°C** → PWM scales linearly from 0 to 255
   - At or above **40°C** → PWM = 255 (motor at full speed)
5. `analogWrite()` sends this PWM value to pin 9, which drives the transistor and controls motor speed.
6. The current temperature and PWM value are printed to the Serial Monitor every 500 ms.

## Arduino Code Explanation

The full sketch is in [`src/temp_sensor_module1.ino`](src/temp_sensor_module1.ino).

- **Pin setup:** `tempPin = A0` (sensor input), `motorPin = 9` (PWM output to transistor/motor).
- **`setup()`:** Configures `motorPin` as an output and starts Serial communication at 9600 baud.
- **`loop()`:**
  - Reads the analog sensor value and converts it to voltage, then to temperature.
  - Uses an `if / else if / else` block to compute the appropriate PWM value based on the temperature thresholds described above.
  - Writes the PWM value to the motor pin with `analogWrite()`.
  - Prints the temperature and PWM value to the Serial Monitor.
  - Waits 500 ms before repeating.

## How to Run the Project

### Option 1: Simulate in Tinkercad (no hardware needed)
1. Open the project in [Tinkercad Circuits](https://www.tinkercad.com/).
2. Recreate the circuit as shown in `images/circuit_diagram.png` (Arduino Uno, TMP36, NPN transistor, resistor, and DC motor on a breadboard).
3. Paste the code from `src/temp_sensor_module1.ino` into the Tinkercad code editor (Text/Blocks toggle → Text).
4. Click **Start Simulation**.
5. Click the TMP36 sensor and adjust its temperature slider to see the motor respond.

### Option 2: Run on Real Hardware
1. Wire the physical components as described in the **Pin Connections** section.
2. Open `src/temp_sensor_module1.ino` in the Arduino IDE.
3. Select **Tools → Board → Arduino Uno** and the correct COM port.
4. Click **Upload**.
5. Open the **Serial Monitor** (baud rate: 9600) to view live temperature and PWM readings.

## Simulation Instructions

- The circuit was built and tested entirely in **Tinkercad Circuits**.
- View and run the live simulation here: [Temp Sensor Module – Tinkercad](https://www.tinkercad.com/things/goHtTPO88dH-temp-sensor-module?sharecode=uwnz_OvLzg12C0WFEN6wZo9UNDbbfh233lKPFju47t0)
- In the simulator, the TMP36 component includes a temperature slider (visible in the Tinkercad properties panel) that lets you manually change the simulated temperature and observe the motor's response in real time.

## Expected Output / Results

- At temperatures **below 27°C**, the motor remains **off** (PWM = 0).
- As temperature rises **between 27°C and 40°C**, the motor speed **increases proportionally**.
- At **40°C and above**, the motor runs at **full speed** (PWM = 255).
- The Serial Monitor displays continuously updating output in the form:
  ```
  Temp: 22.0C, PWM: 0
  Temp: 24.5C, PWM: 0
  Temp: 27.0C, PWM: 0
  Temp: 28.3C, PWM: 25
  Temp: 30.1C, PWM: 60
  Temp: 31.5C, PWM: 88
  Temp: 33.8C, PWM: 133
  Temp: 35.2C, PWM: 160
  Temp: 37.0C, PWM: 196
  Temp: 38.6C, PWM: 227
  Temp: 40.2C, PWM: 255
  Temp: 41.0C, PWM: 255
  ```
  (see `sample_serial_output.txt` for this full sample log)

## Conclusion

This project demonstrates a simple, closed-loop smart temperature monitoring and fan control system using an Arduino Uno, a TMP36 analog sensor, and PWM-based motor control through a transistor switch. It shows the fundamentals of analog sensing, signal conversion, conditional logic, and PWM output — core concepts in embedded systems and automation — and was fully validated through Tinkercad simulation before (optionally) being built on real hardware.

## Project Folder Structure

```
Smart-Temperature-Monitoring-System-with-Automatic-Fan-Control/
├── README.md
├── src/
│   └── temp_sensor_module1.ino
├── images/
│   └── circuit_diagram.png
└── sample_serial_output.txt
```

---

### Author
**Aravind Tagore Gongada**
