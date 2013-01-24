#include <SPI.h>

#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <util.h>

#include <Servo.h>

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,2,177);
IPAddress gateway(192,168,2,1);
IPAddress subnet(255, 255, 0, 0);

EthernetServer server(44);
Servo myServo;

void setup(){
  Ethernet.begin(mac,ip,gateway,subnet);
  server.begin();
  myServo.attach(9);
  myServo.write(0);
  Serial.begin(9600);
  while(!Serial);
  
  Serial.println("Setup successful");
  Serial.println(Ethernet.localIP());
}

void loop(){
  EthernetClient client = server.available();
  
  if(client && client.available()){
    char sentChar = client.read();
    if(sentChar == 'u'){
      myServo.write(90);
      Serial.println("Unlocked");
    }
    else if(sentChar == 'l'){
      myServo.write(0);
      Serial.println("Locked");
    }
  }
}
    
    


