#ifndef WIFUDP_H_
#define WIFUDP_H_
#include "main.h"
#include <WiFiUdp.h>

extern WiFiUDP Udp;
extern WiFiUDP udpSend;

// const char* ssid;
// const char* password;


// unsigned int localUdpPort;  // local port to listen on
extern char incomingPacket[];  // buffer for incoming packets
extern int packetSize;

// const char * udpAddress;
// const int udpPort;

void WIFI_Connect();
void SetupWifi();
int UdpRead();
int UdpReadSize();
// void connectToWiFi(const char *ssid, const char *pwd);
// void WiFiEvent(WiFiEvent_t event);

#endif
