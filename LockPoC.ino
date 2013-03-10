#include <SPI.h>

#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <util.h>

#include <Servo.h>

//MAC Address, this is written on the ethernet shield but can be set to any value.
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//The local network IP address of the ethernet shield.
IPAddress ip(192,168,1,177);
//The IP address of the router that the arduino is connected to.  Generally this is 192.168.1.1 for most routers.
IPAddress gateway(192,168,1,1);
//Subent mask, I'm not sure exactly what this does but all code examples have it set to 255.255.0.0
IPAddress subnet(255, 255, 0, 0);

//Create an EthernetServer object called server, set to listen for traffic on port 44 (This can be any number of your choice, I chose 44 arbitrarily.)
EthernetServer server(44);
//Create the object to control the servo
Servo myServo;

void setup(){
  //Initialize the ethernet shield
  Ethernet.begin(mac,ip,gateway,subnet);
  //Start the ethernet server listening on port 44 defined above.
  server.begin();
  //Tell the servo object which pin the control pin of the servo is connected to, in the example it was connected to pin 9 on the arduino.
  myServo.attach(9);
  //Set the servo to position 0 degreees
  myServo.write(0);
  //Start a serial connection so the arduino serial monitor can be used for debugging.
  Serial.begin(9600);
  while(!Serial);
  //Print a debugging message indicating that the ethernet shield is working correctly.
  Serial.println("Setup successful");
  Serial.println(Ethernet.localIP());
}

void loop(){
  //Server.available() returns a EthernetClient object containing any data that the server received.
  EthernetClient client = server.available();
  
  //If the client object is not null and data is available, read the data.
  if(client && client.available()){
    char sentChar = client.read();
    //If the data received is the character u, rotate the servo to position 90 degrees.
    if(sentChar == 'u'){
      myServo.write(90);
      Serial.println("Unlocked");
    }
    //If the data received is the character l, rotate the servo to position 0 degrees.
    else if(sentChar == 'l'){
      myServo.write(0);
      Serial.println("Locked");
    }
  }
}
    
    


