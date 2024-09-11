/***************************************************************************
 * Sketch Name: Intrusion Detection System
 * Description: This sketch illustrates how Arduino can publish an MQTT
                message
 * Created On:  March 01, 2016
 * Author:      Adeel Javed
 * Book:        Building Arduino Projects for the Internet of Things
 * Chapter:     Chapter 05 - IoT Patterns: Realtime Clients
 * Website:     http://codifythings.com
 **************************************************************************/

/***************************************************************************
 * External Libraries
 **************************************************************************/

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

/*****************************************************************************
 * Internet Connectivity Setup - Variables & Functions
 ****************************************************************************/

// Network configuration
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 200); // IP do Arduino
IPAddress myDns(192, 168, 1, 1); // IP do DNS, pode ser o do roteador ou outro servidor DNS

EthernetClient ethClient;
PubSubClient pubSubClient(ethClient);

// IP address of the MQTT broker
IPAddress mqttServer(192, 168, 1, 213);
int port = 1883;
char topic[] = "codifythings/intrusiondetection";

void connectToInternet() 
{
  // Inicia o shield Ethernet
  Ethernet.begin(mac, ip, myDns);
  
  // Aguardar até obter um IP
  delay(1000);
  
  Serial.print("[INFO] IP Address: ");
  Serial.println(Ethernet.localIP());
}

/*****************************************************************************
 * Sensor Setup - Variables & Functions
 ****************************************************************************/

int calibrationTime = 30;        
long unsigned int lowIn;         
long unsigned int pause = 5000;  
boolean lockLow = true;
boolean takeLowTime;  
int pirPin = 3;

void calibrateSensor()
{
  pinMode(pirPin, INPUT);
  digitalWrite(pirPin, LOW);

  Serial.println("[INFO] Calibrating Sensor ");
  
  for(int i = 0; i < calibrationTime; i++)
  {
    Serial.print(".");
    delay(1000);
  }
  
  Serial.println("");
  Serial.println("[INFO] Calibration Complete");
  Serial.println("[INFO] Sensor Active");
 
  delay(50);
}

void readSensorData()
{
  if(digitalRead(pirPin) == HIGH)
  {
    if(lockLow)
    {  
      lockLow = false;            
      Serial.print("[INFO] Activity Detected @ ");
      Serial.print(millis()/1000);
      Serial.print(" secs"); 
      Serial.println("");        
       
      // Publish sensor data to MQTT broker
      publishSensorData();
       
      delay(50);
    }         
     
    takeLowTime = true;
  }
  
  if(digitalRead(pirPin) == LOW)
  {       
    if(takeLowTime)
    {
      lowIn = millis();
      takeLowTime = false;
    }
      
    if(!lockLow && millis() - lowIn > pause)
    {  
      lockLow = true;                        

      Serial.print("[INFO] Activity Ended @ ");      //output
      Serial.print((millis() - pause)/1000);
      Serial.print(" secs"); 
      Serial.println("");
        
      delay(50);
    }
  }   
}

/*****************************************************************************
 * Data Publish - Variables & Functions
 ****************************************************************************/

void callback(char* topic, byte* payload, unsigned int length)
{
  //Handle message arrived
}

void publishSensorData()
{
  // Conectar ao MQTT Broker
  if (!pubSubClient.connected()) 
  {
    Serial.println("[INFO] Connecting to MQTT Broker");

    if (pubSubClient.connect("arduinoIoTClient")) 
    {
      Serial.println("[INFO] Connection to MQTT Broker Successful");
    }
    else
    {
      Serial.print("[ERROR] Connection to MQTT Broker Failed, rc=");
      Serial.print(pubSubClient.state());
      Serial.println();
      return;
    }
  }

  // Publicar no tópico MQTT
  if (pubSubClient.connected()) 
  {    
    Serial.println("[INFO] Publishing to MQTT Broker");
    pubSubClient.publish(topic, "Intrusion Detected");
    Serial.println("[INFO] Publish to MQTT Broker Complete");
  }
}

/*****************************************************************************
 * Standard Arduino Functions - setup(), loop()
 ****************************************************************************/

void setup() 
{
  // Inicializar a porta serial
  Serial.begin(9600);

  // Conectar Arduino à Internet
  connectToInternet();  
  
  // Configurar PubSubClient
  pubSubClient.setServer(mqttServer, port);
  
  // Calibrar sensor de movimento  
  calibrateSensor();    
}

void loop() 
{  
  // Manter conexão com o broker MQTT
  if (!pubSubClient.connected()) 
  {
    connectToInternet();
  }
  
  pubSubClient.loop();

  // Ler dados do sensor
  readSensorData();
}

