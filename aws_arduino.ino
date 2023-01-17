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
