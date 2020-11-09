#include "Arduino.h"
#include "main.h"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>


WiFiUDP Udp;
WiFiUDP udpSend;

const char *ssid = "Skylights";
const char *password = "magicmods";

// char incomingPacket[26];  // buffer for incoming packets
unsigned int localUdpPort = 9000; // local port to listen on

#define ledPin D2

const char *udpAddress = "192.168.0.30";
const int udpPort = 9000;

// credentials for ESP8266 STA
// const char *sta_ssid1 = "VM4320118";
// const char *sta_password1 = "m4nKrBcvgtkw";

const char *sta_ssid1 = "MagicMods";
const char *sta_password1 = "Sx35018650";

IPAddress IPAP(192, 168, 0, 20);
IPAddress gatewayAP(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

const char *HOSTNAME = "skylights";
WiFiServer server(80);

char incomingPacket[10];
int packetSize = 0;

void SetupWifi()
{
  pinMode(ledPin, OUTPUT);
  // WiFi.hostname(HOSTNAME);
  WiFi.mode(WIFI_STA);
  WiFi.begin(sta_ssid1, sta_password1);
  WiFi.config(IPAP, gatewayAP, subnet);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
    digitalWrite(ledPin, HIGH);
  }
  // if (!MDNS.begin(HOSTNAME))
  // {
  //   Serial.println("Error setting up MDNS responder!");
  // }
  // digitalWrite(ledPin, LOW);
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

// //wifi event handler
// void WiFiEvent(WiFiEvent_t event)
// {
//   switch (event)
//   {
//   case SYSTEM_EVENT_STA_GOT_IP:
//     // When connected set
//     Serial.print("WiFi connected! IP address: ");
//     Serial.println(WiFi.localIP());
//     // initializes the UDP state
//     // This initializes the transfer buffer
//     udp.begin(WiFi.localIP(), udpPort);
//     //      tcpServer.begin();

//     Serial.printf("Wifi Event running on core %d", (int)xPortGetCoreID());
//     Serial.println();

//     connected = true;

//     break;
//   case SYSTEM_EVENT_STA_DISCONNECTED:
//     Serial.println("WiFi lost connection");
//     connected = false;
//     break;
//   }
// }