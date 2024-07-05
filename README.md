Para la ejecución del código se procede a los siguientes pasos:

1.Para la conexión del Arduido a los módulos como el RTC, el relé  y la pantalla OLED se utilizó la siguiente configuración a la cual puede ser accedida a partir del siguiente enlace:
https://wokwi.com/projects/398990290356608001

2.Una vez listo el hardward se procede a abrir el entorno de Arduino IDE y pegar el código del proyecto.

3.Se procede a conectar el Arduino y cargar el código a el.

4.Una vez cargado el código se despliega una menú en la pantalla OLED.

El funcionamiento del código consiste en un menú en el cual podemos acceder mediante dos botones a 4 funciones las cuales especificaremos a continuación:

1.Datos: Se encarga de mostrar la fecha, la temperatura junto con la información del día y mes en que se inicio el cultivo.

2.Reset cultivo: Se encarga de almacenar los datos del dia y el mes actual para iniciar de nuevo el cultivo.
para poder almacenar los datos en la memoria EEPROM es necesario bajar el apagador 2, cuando esto se haga se mostraran unos mensajes en pantalla avisando que los datos se guardaron.

3.Gladiolo: Esta es una de las dos funciones principales, en esta función se encuentran los horarios y las funcionalidades para poder automatizar la iluminación del cultivo de Gladiolos.

4.Tomate: Esta es otra de las funciones principales con las cuales podemos automatizar la iluminación del cultivo de tomates, esta es una opción extra que se deseo agregar 

5.Apagador 1: Se nos ocurrió la idea de poner un apagar el cual cuando dejemos prendido una vez arranque el Arduino procederá a entrar directamente a la función Gladiolo, brincándose el menú esto por si se va la electricidad cuando el Arduino arranque de nuevo vuelva a la función necesaria para que se mantengan prendida o apagada la lampara, esto para que el cultivo no se vea perjudicado

Si queremos salir al menú es cuestión de apretar uno de los botones y regresamos al menú de inicio
