//librerías
#include "SPIFFS.h" //leer los archivos que contienen las credenciales para poder enviar datos a iot core
#include <WiFiClientSecure.h> //libreria que permite conectar esp32 a una red wifi
#include <Wire.h> //libreria para enviar datos desde el monitor
#include <PubSubClient.h> //libreria para publicar y suscribirnos a un tema y recibir o enviar mensajes mqtt
#include <DHT.h> // libreria que permite configurar y obtener datos de sensores 
#include <ESPDateTime.h> // libreria utilizada para obtener la hora y fehca 


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

//Configurara de DHTXX
#define DHTPIN1 4 //Pin
#define DHTPIN2 2 //Pin
DHT dht1(DHTPIN1, DHT11); //Modelo
DHT dht2(DHTPIN2, DHT11); //Modelo
const int relay1 = 14;
const int relay2 = 27;

// metodo para obtener fecha y hora
void NTPConnect(void) {
  DateTime.setServer("ntp.ubuntu.com");
  DateTime.setTimeZone("CET-1CEST");
  DateTime.begin();
  if (!DateTime.isTimeValid()) {
    Serial.println("NTP server: fail.");
  } else {
    Serial.printf("Date Now is %s\n", DateTime.toISOString().c_str());
  }
}


//metodo para conectar una red Wifi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando.. ");
  Serial.println(red);

  WiFi.begin(red, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());
}

//Callback
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

//Conectar el broker MQTT
void reconnect() {

  // Loop para reconección
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    // Creando un ID como ramdon
    String clientId = "ESP32-";
    clientId += String(random(0xffff), HEX);

    // Intentando conectarse
    if (client.connect(clientId.c_str())) {
      Serial.println("conectada");

      // Conectado, publicando un payload...
      client.publish("ei_out", "hello world");

      // ... y suscribiendo
      client.subscribe("ei_in");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" Esperando 5 segundos");

      // Tiempo muerto de 5 segundos
      delay(5000);
    }
  }
}

void setup() {

  Serial.begin(115200);
  dht1.begin();
  dht2.begin();
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  Serial.setDebugOutput(true);
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  ledcSetup(canal,frec,resolucion);
  ledcAttachPin(audio, 0);

  // Inicializa con el PIN led2.
  pinMode(2, OUTPUT);
  setup_wifi();
  delay(1000);

  //leer credenciales de archivos para conectar con el objeto creado en iotcore
  if (!SPIFFS.begin(true)) {
    Serial.println("Se ha producido un error al montar SPIFFS");
    return;
  }
  File file2 = SPIFFS.open("/AmazonRootCA1.pem", "r");
  if (!file2) {
    Serial.println("No se pudo abrir el archivo para leerlo");
    return;
  }
  Serial.println("Root CA File Content:");
  while (file2.available()) {
    Read_rootca = file2.readString();
    Serial.println(Read_rootca);
  }
  File file4 = SPIFFS.open("/5342f3f29-certificate.pem.crt", "r");
  if (!file4) {
    Serial.println("No se pudo abrir el archivo para leerlo");
    return;
  }
  Serial.println("Cert File Content:");
  while (file4.available()) {
    Read_cert = file4.readString();
    Serial.println(Read_cert);
  }
  File file6 = SPIFFS.open("/5342f3f29-private.pem.key", "r");
  if (!file6) {
    Serial.println("No se pudo abrir el archivo para leerlo");
    return;
  }
  Serial.println("privateKey contenido:");
  while (file6.available()) {
    Read_privatekey = file6.readString();
    Serial.println(Read_privatekey);
  }
  char* pRead_rootca;
  pRead_rootca = (char *)malloc(sizeof(char) * (Read_rootca.length() + 1));
  strcpy(pRead_rootca, Read_rootca.c_str());

  char* pRead_cert;
  pRead_cert = (char *)malloc(sizeof(char) * (Read_cert.length() + 1));
  strcpy(pRead_cert, Read_cert.c_str());

  char* pRead_privatekey;
  pRead_privatekey = (char *)malloc(sizeof(char) * (Read_privatekey.length() + 1));
  strcpy(pRead_privatekey, Read_privatekey.c_str());

  Serial.println("================================================================================================");
  Serial.println("Certificados que pasan adjuntan al espClient");
  Serial.println();
  Serial.println("Root CA:");
  Serial.write(pRead_rootca);
  Serial.println("================================================================================================");
  Serial.println();
  Serial.println("Cert:");
  Serial.write(pRead_cert);
  Serial.println("================================================================================================");
  Serial.println();
  Serial.println("privateKey:");
  Serial.write(pRead_privatekey);
  Serial.println("================================================================================================");

  espClient.setCACert(pRead_rootca);
  espClient.setCertificate(pRead_cert);
  espClient.setPrivateKey(pRead_privatekey);

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  //**************
  WiFi.macAddress(mac);
  snprintf(mac_Id, sizeof(mac_Id), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.println(mac_Id);
  //**************
  delay(2000);
}


void loop() {

  // obtener datos del sensor dth
  float h1 = dht1.readHumidity();         // Lectura de Temperatura criadora
  float t1 = dht1.readTemperature();      // Lectura de humedad criadora
  float h2 = dht2.readHumidity();         // Lectura de Temperatura exterior
  float t2 = dht2.readTemperature();      // Lectura de humedad exterior
  if (isnan(h1 and h2) || isnan(t1 and t2))
  {
    Serial.println("¡Error al leer del sensor DHT!");
    return;
  }

  if (!client.connected()) {
    reconnect();
  }


  client.loop();

  long now = millis();
  if (now - lastMsg > 5000) {  // el tiempo transcurre cada que se envia un mensaje a la cloud y se ejecutan las condiciones 
    lastMsg = now;

    String macIdStr = mac_Id; 
    String Temperatura1 = String(t1); //temperatura criadora
    String Humedad1 = String(h1);     //humedad criadora
    String Temperatura2 = String(t2); //temperatura exterior
    String Humedad2 = String(h2);     //humedad exterior
    String fecha = String(DateTime.toISOString()); // fecha y hora actual
    // condicion cuando la temperatura de la criadora sea menor a 30° (temeratura baja) se encienda la fuente de calor,
    // se apaguen los ventiladores, el bafle emita un sonido de alarma y el led rgb genere una luz de color azul
    if (t1 < 30)
    {
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, LOW);
      digitalWrite(pinR, LOW);
      digitalWrite(pinG, LOW);
      digitalWrite(pinB, HIGH);
      frec=300;
      ledcWriteTone(0, frec);
    } 
    // condicion cuando la temperatura de la criadora este entre 30° y 33° (rango normal)la fuente de calor permanezca encendida,
    // se apaguen los ventiladores y el led rgb genere una luz de color verde
    if (t1 >=30 and t1 <=33) {
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, LOW);
      digitalWrite(pinR, LOW);
      digitalWrite(pinG, HIGH);
      digitalWrite(pinB, LOW);
      frec=0;
      ledcWriteTone(0, frec);
    }
    // condicion cuando la temperatura de la criadora sea superior a 33° (temperatura alta) la fuente de calor se apague,
    // se enciendan los ventiladores, el bafle emita un sonido de alarma y el led rgb genere una luz de color Roja
    if (t1 >=30 and t1 <=33) {
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, LOW);
      digitalWrite(pinR, HIGH);
      digitalWrite(pinG, LOW);
      digitalWrite(pinB, LOW);
      frec=300;
      ledcWriteTone(0, frec);
    }
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
}
