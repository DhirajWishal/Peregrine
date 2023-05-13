# Architecture ✏️

The controller source is made of up 4 main parts.

1. Core.
    - This is where all the core objects are stored.
    - Location: `src/core/`.
2. Algorithms.
    - This is where all the algorithms used by the different systems are placed.
    - Location: `src/algorithms/`.
3. Systems.
    - This is where all the major systems of the controller are placed.
    - Location: `src/systems/`.
    - There are 3 main systems.
        - Input system.
        - Output system.
        - Stabilizing system.
4. Components
    - This is where all the components used by the systems are placed.
    - Location: `src/components/`.

The drone is controlled by the different systems in the controller that uses components and algorithms for different purposes. For example, the stabilizing system uses the `MPU6050` sensor which is a component. This component then uses the [Kalman filter](https://en.wikipedia.org/wiki/Kalman_filter) to filter the sensor's noise.

The basic system architecture is that the input system gathers the inputs using a data link. These data links include a default data link used for debugging, and FS-i6 data link that uses the FlySky receiver. These inputs are taken in as throttle, pitch, roll and yaw. These inputs are forwarded to the stabilizer which uses the `MPU6050` sensor's readings (after going through the Kalman filter) to calculate the final output values that are provided to the output system. The output system then uses these outputs to control the servo motors and the rotors depending on the fly mode.

The controller has 2 main fly modes.

1. Hover mode.
    - In this mode the drone acts as a normal transverse rotor helicopter.
    - Both the rotors are rotated upwards.
    - The throttle value is directly proportional to the rotors' speed.
    - The pitch value is controlled by pitching the rotors together, forward or backwards.
    - The roll value is controlled by increasing the rotor speed on the left or right wing depending on the value.
    - The yaw value is controlled by tilting the rotors in the opposite directions.
2. Cruise mode.
    - In this mode the drone acts as a normal plane with wing mounted propellers.
    - Both the rotors are rotated 90 degrees forward.
    - The throttle value is directly proportional to the rotors' speed.
    - The pitch value is controlled by pitching thr rotors together, up or down. It also uses the elevator of the drone.
    - The roll value is controlled by tilting the rotors in the opposite directions.
    - The yaw value is controlled by increasing the rotor speed on the left or right wing depending on teh value. It also uses the rudder of the drone.

The drone should start in the hover mode when powering on and can be switched to cruise mode once it's in the air. The drone can stop in the cruise mode but it's recommended to be switched to the hover mode to bring it to a standstill. Note that in terms of power consumption, the drone uses way less power on the cruise mode compared to hover mode since the servo motors and rotors doesn't need to be updated that much.
