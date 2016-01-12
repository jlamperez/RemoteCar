REMOTE CAR
==========

1.-Se utilizar�n los Switches para hacer mover el coche.
SW(G15) = 1 -> Forward
SW(P15) = 1 -> Backward
SW(W13) = 1 -> Right
SW(T16) = 1 -> Left 
All SW = 0  -> Stop

2.-Si en hw_services la carpeta importada es display_vga se 
visualizar�n los movimientos del coche por pantalla.
Si en hw_services la carpeta importada es display_uart se
podr� monitorizar mediante uart.

3.-Los Estados en los que puede estar el coche son:
-STOPPED
-GOING_FORWARD
-GOING_BACK
-GOING_RIGHT
-GOING_LEFT
Se utiliza una macro para la m�quina de estados.

4.-La aplicaci�n podr�a separarse en dos: Por un lado la parte del car_controller y 
por otro lado la parte del remote_control. Estos se envian mensajes mediante un 
buffer circular.

5.-Me queda por implementar mejor los archivos car_register.h y .c
6.-Me gustaría quedar contigo para ver lo de la maquina de estados para coche autonomo.
Mas informacion en https://github.com/jlamperez/RemoteCar[En construccion]