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

### Librerias a instalar:
```
//librerías
#include "SPIFFS.h" //leer los archivos que contienen las credenciales para poder enviar datos a iot core
#include <WiFiClientSecure.h> //libreria que permite conectar esp32 a una red wifi
#include <Wire.h> //libreria para enviar datos desde el monitor
#include <PubSubClient.h> //libreria para publicar y suscribirnos a un tema y recibir o enviar mensajes mqtt
#include <DHT.h> // libreria que permite configurar y obtener datos de sensores 
#include <ESPDateTime.h> // libreria utilizada para obtener la fecha y hora. 
```


## Software ArduinoIDE
En este software importaron diferentes librerías para el funcionamiento de los dispositivos a utilizar imagen(4) y se configuraron los sensores dth11 para obtener la información de la temperatura y la humedad, se configuraron las siguientes condiciones: 
•	cuando la temperatura de la criadora sea menor a 30° (temperatura baja) se encienda la fuente de calor, se apaguen los ventiladores, el bafle emita un sonido de alarma y el led rgb genere una luz de color azul.
•	Cuando la temperatura de la criadora este entre 30° y 33° (rango normal) la fuente de calor permanezca encendida, se apaguen los ventiladores y el led rgb genere una luz de color verde.
•	Cuando la temperatura de la criadora sea superior a 33° (temperatura alta) la fuente de calor se apague, se enciendan los ventiladores, el bafle emita un sonido de alarma y el led rgb genere una luz de color Roja.
Las condiciones mencionadas anteriormente generan alertas que permiten informarle al usuario en qué condiciones se encuentra la criadora. Se configura la placa de desarrollo esp32 asignándole unas credenciales de red wifi y del servidor MQTT para que cuando este en funcionamiento la placa de desarollo se conecte a internet y pueda enviar un mensaje en formato Json a la plataforma IOTcore de aws. 
```
//librerías
#include "SPIFFS.h" //leer los archivos que contienen las credenciales para poder enviar datos a iot core
#include <WiFiClientSecure.h> //libreria que permite conectar esp32 a una red wifi
#include <Wire.h> //libreria para enviar datos desde el monitor
#include <PubSubClient.h> //libreria para publicar y suscribirnos a un tema y recibir o enviar mensajes mqtt
#include <DHT.h> // libreria que permite configurar y obtener datos de sensores 
#include <ESPDateTime.h> // libreria utilizada para obtener la fecha y hora. 


//configuracion de servidor, hora de verano para obtener hora y fecha
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -18000;
const int   daylightOffset_sec = 0;


//nombre y contraseña de red Wifi
const char* red = "DESKTOP-9F81IOV 0670";
const char* password = "6D562<r8";

//configuraciones para conectar al servidor MQTT
const char* mqtt_server = "a2slv14r79tw7t-ats.iot.us-east-1.amazonaws.com";
const int mqtt_port = 8883;
// definicion de variables
String Read_rootca;
String Read_cert;
String Read_privatekey;
String asd;
// pines led rgb
int pinR = 18;
int pinG = 19;
//pin bafle
int audio = 26;
int canal=0, frec=250, resolucion=8;
#define BUFFER_LEN  256
long lastMsg = 0;
char msg[BUFFER_LEN];
int value = 0;
byte mac[6];
char mac_Id[18];
int count = 1;
//Configuración de cliente MQTT
WiFiClientSecure espClient;
PubSubClient client(espClient);
```

## Protocolo MQTT
Con el protocolo MQTT se envia un mensaje por internet de la placa esp32 a a la plataforma IOTcore, este mensaje tiene un formato Json y contiene: la dirección mac, la temperatura y humedad de la criadora y del medio ambiente externo y la fecha y hora en que se realizó la lectura de dichos valores. En la imagen(5) se visualiza la cadena de texto en la que se especifican las variables que se envían a través del protocolo.

```
 // cadena de texto en formato que se envia a iotcore
    snprintf (msg, BUFFER_LEN, "{\"mac_Id\" : \"%s\", \"Temperatura1\" : %s, \"Humedad1\" : %s, \"Temperatura2\" : %s, \"Humedad2\" : %s, \"Fecha_hora\" : \"%s\"}",
    macIdStr.c_str(), Temperatura1.c_str(), Humedad1.c_str(), Temperatura2.c_str(), Humedad2.c_str(), fecha.c_str());
    Serial.print("Publicando mensaje: ");
    Serial.print(count);
    Serial.println(msg);
    client.publish("sensor", msg);
    count = count + 1;
  }
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
 ```
##	Modelo electrónico del sistema
En el modelo electrónico (ilustración 3) se puede observar las conexiones realizadas para darle solución al proyecto.

![Buscar Libreria](https://github.com/Zasalast/Esp32-D1-Criadora-de-Pollos/blob/main/esp32/modelo-electronico.jpg)
