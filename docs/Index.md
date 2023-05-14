# Peregrine 🦅

Peregrine is a VTOL drone flight controller intended to run on an ESP32 board. The controller supports tilt rotor and tilt wing drones (since they both use the same principal). The controller can be controlled from a FlySky FS-i6 controller. Optionally we're also going to add support to the [Nrf24l01+pa+lna](https://www.sparkfun.com/datasheets/Components/SMD/nRF24L01Pluss_Preliminary_Product_Specification_v1_0.pdf) transceiver module.

## Usage 🍃

The controller repository is based on [PlatformIO](https://platformio.org/) so start by installing the PlatformIO extension to [Visual Studio Code](https://platformio.org/install/ide?install=vscode). After installing the extension and setting up the SDK, clone this repository to a local directory and open the directory using VS Code using the following commands.

```sh
git clone https://github.com/Nexonous/Peregrine
cd Peregrine
code .
```

After opening the folder in VS Code, head to the PlatformIO extension and start by building the `esp32-debug` target. Once it gets built without an issue, you can connect the ESP32 board to the computer, setup the correct port and upload the code to the controller using the 'Upload and Monitor' task. We recommend running the debug target before uploading the release target to test if everything is working properly. Once everything is sorted out and if everything is working fine, you can upload the release build to the controller.

***Please note that the controller is still in it's early stages and might not even work. So please don't use this as long as this notice is up!***

## License ⚖️

This repository is licensed under [Apache-2.0](https://github.com/Nexonous/Peregrine/blob/release/LICENSE).
