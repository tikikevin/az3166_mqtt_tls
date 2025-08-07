// MQTTClient_Socket_Sample.cpp
// Example of using MQTTClient with a TLS socket network

#include "MQTTClient.h"
#include "MQTTNetwork.h"    // for Countdown or you can roll your own
#include "TLSSocketNetwork.h"

extern const char rootCACert[];  // store PEM in PROGMEM or SPIFFS

void setup() {
  Serial.begin(115200);
  MXCHIPPlatform_Init();       // Wi-Fi, DNS, NTP
  DeviceNetwork_Init();

  // --- Prepare TLS network ---
  TLSSocketNetwork net;
  net.setCACert((const unsigned char*)rootCACert, strlen(rootCACert));

  // --- Bind MQTT client to our TLS network ---
  // Template args: <Network, Timer, MAX_PACKET=100, MAX_HANDLERS=5>
  MQTT::Client<TLSSocketNetwork, Countdown> mqtt(net);

  // --- Connect over TLS on port 8883 ---
  MQTTPacket_connectData opts = MQTTPacket_connectData_initializer;
  opts.MQTTVersion      = 3;
  opts.clientID.cstring = (char*)"AZ3166-TLS";  
  if (mqtt.connect(opts) != MQTT::SUCCESS) {
    Serial.println("❌ MQTT/TLS connect failed");
    while (1) { delay(1000); }
  }
  Serial.println("✅ Connected MQTT over TLS!");
}

void loop() {
  mqtt.yield(1000);  // keep-alive & receive
  // …publish/subscribe as usual…
}