#include "Arduino.h"
#include "main.h"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>


WiFiUDP Udp;
WiFiUDP udpSend;
bool connected = false;
    // const char *ssid = "Skylights";
    // const char *password = "magicmods";

    // char incomingPacket[26];  // buffer for incoming packets
    unsigned int localUdpPort = 9000; // local port to listen on

const char* udpAddress = "192.168.0.110";
const int udpPort = 9000;

// credentials for ESP8266 STA
// const char *sta_ssid1 = "VM4320118";
// const char *sta_password1 = "m4nKrBcvgtkw";

const char* sta_ssid1 = "MagicMods";
const char* sta_password1 = "Sx35018650";

IPAddress IPAP(192, 168, 0, 110);
IPAddress gatewayAP(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

const char *HOSTNAME = "skylights";
WiFiServer server(80);
// WiFiEventHandler WiFiEvent_t;

char incomingPacket[10];
int packetSize = 0;

void WIFI_Connect()
{
  WiFi.disconnect(true);
  Serial.println("Wifi STA Begin...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(sta_ssid1, sta_password1);
  WiFi.config(IPAP, gatewayAP, subnet);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
  }
  digitalWrite(LED_BUILTIN, HIGH);
  // Wait for connection
  for (int i = 0; i < 25; i++)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      delay(250);
      digitalWrite(LED_BUILTIN, LOW);
      Serial.print(".");
      delay(250);
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
  digitalWrite(LED_BUILTIN, HIGH);
}


void SetupWifi()
{
  // WiFi.hostname(HOSTNAME);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  // WiFi.onEvent(WiFiEvent);
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WIFI_Connect();
  Udp.begin(localUdpPort);
}

int UdpReadSize()
{
  int packetSize = Udp.parsePacket();
  return packetSize;
}
int UdpRead()
{
  packetSize = Udp.parsePacket();
  int len = Udp.read(incomingPacket, packetSize);
  // Serial.println(int(incomingPacket));
  return packetSize;
}


// Arrays index
//3 = Brightness
//4 = Saturation
//2 = Color
//5 = Palettes
//6 = Speed

//10 = Bed
//11 = Desk
//12 = Ceilling
//13 = Window
 
//15 Timer

// void connectToWiFi(const char *ssid, const char *pwd)
// {
//   Serial.println("Connecting to WiFi network: " + String(ssid));

//   // delete old config
//   WiFi.disconnect(true);
//   //register event handler
//   WiFi.onEvent(WiFiEvent);

//   //Initiate connection
//   WiFi.begin(ssid, pwd);

//   Serial.println("Waiting for WIFI connection...");
// }

//wifi event handler
// void WiFiEvent(WiFiEvent_t event)
// {
//   switch (event)
//   {
//   case WIFI_EVENT_STAMODE_GOT_IP:
//     // When connected set
//     Serial.print("WiFi connected! IP address: ");
//     Serial.println(WiFi.localIP());
//     // initializes the UDP state
//     // This initializes the transfer buffer
//     // Udp.begin(WiFi.localIP(), udpPort);
//     //      tcpServer.begin();

//     Serial.println();
//     Udp.begin(localUdpPort);
//     connected = true;

//     break;
//   case WIFI_EVENT_STAMODE_DISCONNECTED:
//     Serial.println("WiFi lost connection");
//     connected = false;
//     break;
//   }
// }