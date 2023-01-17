# Esp32-D1-Criadora-de-Pollos

La biblioteca SPIFFS se utiliza para leer archivos en la memoria flash del ESP32. En este caso, se está utilizando para leer los archivos que contienen las credenciales para conectarse a IoT Core.
La biblioteca WiFiClientSecure se utiliza para conectar el ESP32 a una red Wi-Fi de forma segura.
La biblioteca Wire permite la comunicación entre el ESP32 y otros dispositivos mediante el protocolo I2C.
La biblioteca PubSubClient se usa para conectarse a un servidor MQTT y suscribirse o publicar temas para enviar y recibir mensajes.
La biblioteca DHT se utiliza para configurar y leer datos de sensores DHT.
La biblioteca ESPDateTime se utiliza para obtener la fecha y la hora actuales conectándose a un servidor NTP y configurando la zona horaria.
El código también usa varias variables y constantes para definir la red y la configuración de la conexión MQTT, así como números de pin para 
diferentes sensores y dispositivos, y un búfer para almacenar mensajes. La función NTPConnect() se usa para conectarse a un servidor NTP y configurar
la fecha y la hora, y la función setup_wifi() se usa para conectarse a una red Wi-Fi. La función callback() se usa para manejar los mensajes
entrantes del servidor MQTT.
Este código parece ser para un ESP32, un microcontrolador que puede conectarse a Wi-Fi y otras redes, y utiliza varias bibliotecas para conectarse a diferentes servicios y dispositivos.

Las primeras líneas incluyen las bibliotecas necesarias para que se ejecute el programa.

La biblioteca "SPIFFS.h" es para leer archivos de la memoria flash del ESP32.
La biblioteca "WiFiClientSecure.h" es para conectarse a una red Wi-Fi de forma segura.
La biblioteca "Wire.h" es para comunicarse con otros dispositivos mediante el protocolo I2C.
La biblioteca "PubSubClient.h" es para conectarse a un servidor MQTT, lo que permite suscribirse y publicar temas para enviar y recibir mensajes.
La biblioteca "DHT.h" es para configurar y leer datos de sensores DHT.
La biblioteca "ESPDateTime.h" es para obtener la fecha y la hora actuales conectándose a un servidor NTP y configurando la zona horaria.
El siguiente conjunto de líneas son constantes, definen la red y la configuración de conexión MQTT, así como los números de pin para diferentes sensores y dispositivos, y un búfer para almacenar mensajes.

La constante "ntpServer" es la dirección del servidor a la que conectarse para obtener la fecha y la hora.
"gmtOffset_sec" y "daylightOffset_sec" son constantes para configurar la zona horaria.
Las constantes "red" y "password" son para el nombre y la contraseña de la red Wi-Fi.
Las constantes "mqtt_server" y "mqtt_port" son para la dirección y el puerto del servidor MQTT.
"Read_rootca", "Read_cert" y "Read_privatekey" son variables que se usan para leer los archivos que contienen las credenciales para conectarse a IoT Core.
"pinR", "pinG", "audio", "canal", "frec", "resolucion" son números pin para diferentes sensores y dispositivos.
"lastMsg", "msg", "value", "mac", "mac_Id", "count" son variables utilizadas en diferentes partes del programa.
Las siguientes líneas son definiciones de funciones.

La función "NTPConnect()" se utiliza para conectarse a un servidor NTP y configurar la fecha y la hora.
La función "setup_wifi()" se utiliza para conectarse a una red Wi-Fi.
La función "devolución de llamada ()" se usa para manejar los mensajes entrantes del servidor MQTT.
El resto del código parece usar estas bibliotecas, constantes, variables y funciones para conectarse a una red Wi-Fi, conectarse a un servidor MQTT, leer datos de sensores y controlar dispositivos como LED y relés en función de los datos recibidos.

* Verifica si el código no tiene errores de sintaxis y copilaria de forma correcta cuando cargue en el dispositivo.
![Verificar código ](https://github.com/Zasalast/Esp32-D1-Criadora-de-Pollos/blob/main/esp32/verificar_codigo.jpg)

* Carga el código al dispositivo, en este caso al "ESP32 D1" para luego poder funcionar de acuerdo al codigo de instrucciones proporcionado.
![Cargar Código ](https://github.com/Zasalast/Esp32-D1-Criadora-de-Pollos/blob/main/esp32/cargar_codigo.jpg)

* El gestor de bibliotecas permite instalar las mismas para que los dispositivos puedan ejecutarce de acuerdo a los dispositivos especificos que tienen, como modulos y componentes adicionales, como es el caso de la libreria "DHT.h" que permite entender los datos que envia el sensor y lo convierte a datos.

![Gestionar Bibliotecas](https://github.com/Zasalast/Esp32-D1-Criadora-de-Pollos/blob/main/esp32/gestionar_bibliotecas.jpg)

* El busca la libreria en la bibliotecas para instalar las mismas, para que los dispositivos puedan ejecutarce de acuerdo a los dispositivos especificos que tienen o como "ESPDateTime.h" la libreria utilizada para obtener la fecha y  hora.

![Buscar Libreria](https://github.com/Zasalast/Esp32-D1-Criadora-de-Pollos/blob/main/esp32/buscar_librerias.jpg)

* Instala la libreria, como se menciono anterior mente, las librerias permiten realizar funciones especificas en el desarrollo.

![Instalar Libreria](https://github.com/Zasalast/Esp32-D1-Criadora-de-Pollos/blob/main/esp32/instalar_librerias.jpg)
