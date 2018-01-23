Telescope thermal stabilization
===============
This Arduino sketch is designed for the telescope's thermal stabilization controller. The controller (AVR) receives values from the temperature sensors of the main mirror of the telescope and the environment. Calculating the difference between the temperatures, the controller automatically changes the speed of rotation of the cooler, thus changing the cooling intensity. All readings are output on the LCD 16x4.

Thus, it is useful to know when the telescope mirror is ready for the start of astro photography. In addition, since the ambient temperature during the observation process can fluctuate, the main mirror may not have time to cool down so quickly. The controller is able to automatically control the cooler at low revs, creating a minimal vibration.

### LCD example

|M:+22.4C° D:2.8 |

|O:+19.6C° F:100%|

- **M** - the temperature of the main mirror (in Celsius);
- **O** - air (outside) temperature;
- **D** - the difference between the temperatures;
- **F** - cooler speed in percent.

### Options
```cpp
// --- /CONFIGURATION/ ---
#define DEBUG      // Debug mode (messages are displayed in a serial port)
#define PIN_TEMP 2 // PIN of temperature sensor
#define PIN_FAN  9 // PIN PWM for fan control
// --- /CONFIGURATION/ ---
```
- **DEBUG** - If the line is uncommented - debug messages will be translated into the Serial Monitor, it is used only for debugging, it is necessary to note that to reduce the code size;
- **PIN_TEMP** - a digital pin for connecting the bus of temperature sensors DS18B20, all sensors must be on the same busж;
- **PIN_FAN** - digital pin with PWM for connecting the control wire to the MOSFET transistor, for smooth voltage regulation on the cooler.

----------------------

### Libraries
List of additional (other than standard) libraries

- [OneWire](http://playground.arduino.cc/Learning/OneWire)
- [DallasTemperature](https://github.com/milesburton/Arduino-Temperature-Control-Library)
- [LiquidCrystal](https://github.com/arduino-libraries/LiquidCrystal)