# Enabling/ Disabling Features 🔧

The `core/Configuration.hpp` file contains a couple of pre-compiler definitions which can be commented/ uncommented out for different features.

- Uncomment/ comment out the `PEREGRINE_DATA_LINK_FS_I6` pre-compiler definition if you're using the FS-i6 receiver to control the drone.
- Uncomment/ comment out the `PEREGRINE_DATA_LINK_NRF24L01` pre-compiler definition if you're using the NRF24L01[+PA+LNA] transceiver to control the drone.

***Note that multiple related features can be enabled/ disable in which case a default or the best will be chosen.***
