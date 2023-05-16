# FS-i6 Controller Setup 🎛️

The drone as built-in support for the FS-i6 controller once the proper build is sent to the controller with the FS-i6 receiver. Please look into the [hardware setup](Hardware-Setup.md) file for more information.

When using the FS-i6 radio control system, make sure to define the correct pre-compile definition (please refer to the [enabling/ disabling features](Enabling-Disabling-Features.md) section). And on the transmitter (radio), go to settings and assign the Ch5 (channel 5) to a switch (this could be anything from `SwA`, `SwB`, and `SwD`). This channel is used to switch from Hover mode to Cruise mode.

If you're new to the transmitter, use the following steps to do so.

1. Switch on the transmitter.
2. Hold down the "OK" button till the setting menu pops up.
3. Using the "UP" button, select the "Functions setup" option and press the "OK" button.
4. Using the "DOWN" button, select the "Aux. channels" option in the menu and press the "OK" button.
5. Using the "UP" button, cycle through the source list till it reaches the desired switch.
6. Once selected, press down the "CANCEL" button till you get redirected back to the previous menu.
7. When you're back at the menu, this means the settings has been updated. Now you can press "CANCEL" a couple more times to get back to the main menu.

Setting the fly mode from Hover to Cruise and vice versa from a switch makes it better for the controller and the user since all the switches needs to be on the 'down' position when powering the transmitter. This will also make sure that the controller starts off in Hover mode and does not cause any problems for the operator and anyone or anything nearby.
