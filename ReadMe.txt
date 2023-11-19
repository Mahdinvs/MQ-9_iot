1- MQ-9 Vcc must be connected to 5V DC
2- You can create a dashboard and plot a curve for gas level on thinger.io which is easy.
3- This code samples the gas level every 500 milliseconds and calculates the average every 15 seconds. both are changeable.
4- Remember that whether you generate a credential or create it yourself, don't change it or if you do, make sure you use the right one.
5- To configure MQ-9, connect Vcc to 5V for 24 to 48 hours, and to use it with ESP32, first convert 5V Analog out to 3.3V using either resistors or convert circuits. (connecting 5V to ADC pins of ESP32 might damage it.)
