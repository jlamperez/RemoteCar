# RemoteCar
Implementation of a remote Car

A Zybo Zynq™-7000 Development Board is used to develop this remote car proyect.

Now the switches of the board are used to simulate the remote orders for moving to the car.
SW(G15) = 1 -> Forward
SW(P15) = 1 -> Backward
SW(W13) = 1 -> Right
SW(T16) = 1 -> Left 
All SW = 0  -> Stop

If we import in the hw_service the display_vga folder we are able to see the car movements 
through vga in a screen. In the other hand if we import the display_uart we are able to
monitor the car through UART.

For the implementation of the state machine a macro is used. The states in which the car
can be are:
STOPPED
GOING_FORWARD
GOING_BACK
GOING_RIGHT
GOING_LEFT

The application could be divided in twice: For one hand the part of the car_controller and
and for the other the part of the remote_control. They comunicate between each other using
a circular buffer.
