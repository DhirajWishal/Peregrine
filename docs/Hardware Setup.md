# Hardware Setup 🛠️

The drone can be used as either a tilt rotor or a tilt wing aircraft. But we recommend using a tilt rotor design since it allows us to reduce the load that we give in to the controlling servo motor. The following are the list of parts required by the drone.

| Component                      | Quantity |
|--------------------------------|----------|
| BLDC Motors                    |        2 |
| BLDC Motor Drivers             |        2 |
| Servo Motors                   |        4 |
| MPU60560 sensor                |        1 |
| FS-i6 transmitter/ receiver    |        1 |
| ESP32 dev board                |        1 |
| Drone Power Distribution Board |        1 |
| Drone Battery                  |        1 |
| Drone Propellers               |        2 |

***Note: BLDC stands for Brush-less DC***

Once you have everything ready, start connecting the components to the ESP32 dev board using the following table.

|           Component          | Component's pin/ connection | ESP32 pin number |
|:----------------------------:|:---------------------------:|:----------------:|
|            MPU6050           |             VCC             |        VIN       |
|                              |             GND             |        GND       |
|                              |             SCL             |        22        |
|                              |             SDA             |        21        |
|  Left wing BLDC motor driver |          VCC (Red)          |        VIN       |
|                              |         GND (Brown)         |        GND       |
|                              |       Signal (Yellow)       |        32        |
| Right wing BLDC motor driver |          VCC (Red)          |        VIN       |
|                              |         GND (Brown)         |        GND       |
|                              |       Signal (Yellow)       |        33        |
|        Left wing servo       |          VCC (Red)          |        VIN       |
|                              |         GND (Brown)         |        GND       |
|                              |       Signal (Yellow)       |        25        |
|       Right wing servo       |          VCC (Red)          |        VIN       |
|                              |         GND (Brown)         |        GND       |
|                              |       Signal (Yellow)       |        26        |
|        Elevator servo        |          VCC (Red)          |        VIN       |
|                              |         GND (Brown)         |        GND       |
|                              |       Signal (Yellow)       |        27        |
|         Rudder servo         |          VCC (Red)          |        VIN       |
|                              |         GND (Brown)         |        GND       |
|                              |       Signal (Yellow)       |        14        |
|        FS-i6 receiver        |              RX             |        RX2       |
|                              |              TX             |        TX2       |

Note that the drone motors do not directly connect to the ESP32 dev board. Its power lines (black and red wires) directly connect to the power lines of the distribution board and only the ESC's (Electronic Speed Controller/ motor driver) signal lines connect to the dev board.

## Connecting everything together 🪛

When connecting the MPU6050 sensor, make sure that the sensor's X-axis is parallel to the wing and goes from left to right. This will result in the Y axis pointing directly forward. The sensor should be set upright.

Hereafter, connecting everything else is pretty straightforward. Connect the correct pins to the PWM inputs of the servos/ motor drivers and you're good to go.

If you're using a Flysky FS-i6 transmitter/ receiver module with the drone, the Arduino boards will not be viable since they don't have the required iBus protocol. This leaves us with the ESP32 board. Here you can connect it to the correct pins (which are yet to be defined) and you should be ready to go. You can also use an NRF24L01+PA+LNA Wireless Transceiver to control the drone. Here I believe you can use both types of boards, Arduino or ESP32 but I have yet to test it out.

Tuning the PID algorithm is currently done by editing the constant values in the `src/systems/Stabilizer.hpp` file. We will introduce a better system to tune the PID rather than altering header files.

As mentioned earlier, this can also be used for tilt-wing applications. The servos connect similarly, but here, rather than the servos controlling only the rotors, it also controls the whole wing. This will increase the load the servo motors will have to operate with which will increase the odds of it failing. Make sure to use servos that support large amounts of force with adequate response times to mitigate any unwanted issues.
