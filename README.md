# openSensor

WIP - Using an ESP8266 chip as a web server for home automation purposes.

- This project allows an ESP8266 chip to connect to a wireless network and serve a web server that is accessible within that network.

### Requirements

This project requires:

- [VSCode]()
- [Node.js]()
- [Yarn]()

### Setup / Getting Started

1. Get the [Arduino VSCode extension](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino)
2. Add support for the ESP8266 board:
   2.1. Open the Arduino Board Manager (cmd+shift+p to open command palette in VSCode and then type 'Arduino: Board Manager') and search for 'ESP8266' and install.
   2.2. If you find issues with the previous step, you can have a look at the [Arduino VSCode extension page](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino) or the [ESP8266 community repo README](https://github.com/esp8266/Arduino)
3. Install dependencies by running `yarn`
4. Add an `enviroment.h` file to the `/firmware` folder. See [enviroment variables](#environment-variables).
5. You should now be able to 'verify' this project's code by running the Arduino: Verify command (cmd+shift+p to open command palette and then type 'Arduino: Verify').

### Environment Variables

- The `firmware/environment.h` file should have the following format/content:

```c++
const char SSID[] = "WIFI_NAME";
const char SSID_PASS[] = "WIFI_PASS";
const char INDEX_HTML[] = "";
```

_Note:_ Remember to replace `WIFI_NAME` with the name of a wireless network and `WIFI_PASS` with the network password. The `INDEX_HTML` enviroment variable is automatically pre-populated on build.

### Uploading firmware to chip

- To upload firmware to the ESP8266 chip, you will need to do some setup with your hardware. You might need to provide a 3.3V DC power supply to your ESP8266 and also use a serial-to-USB converter. Here is an [basic wiring diagram](./resources/wiring.jpg), more detailed information can be found in the [beginners' guide](https://tttapa.github.io/ESP8266/Chap02%20-%20Hardware.html).
- Once the ESP8266 has a power supply and is connected to your computer (through the serial-to-USB converter mentioned above), you would be able to upload the firmware/code from this project. To do so, open the command palette in VSCode and type 'Arduino: Upload'.

_Note:_ In order to flash the ESP8266 chip, the GPIO0 pin needs to be connected to GND on start-up (when powering ON the chip). After flashing, rebooting the chip with the GPIO0 pin not connected to GND should make the chip start running this project's code/firmware.

### Trobleshooting

<!-- todo: add some notes related to c_cpp_properties.jso, arduino.json and OS. -->

- TBA

### Useful links / resources

1. [Beginners' guide to ESP8266](https://tttapa.github.io/ESP8266/Chap01%20-%20ESP8266.html)
2. [Pinout diagram](./resources/pinout.png)
