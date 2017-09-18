
// ToDo
// check internet for posibility to increase the baud rate for Software Serial
// clean code for serial prints in loop

#include <SoftwareSerial.h>
SoftwareSerial mySerial(D7, D8); // RX, TX

 
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>                // for sending OSC messages

char ssid[] = "bull&hawk";                 // your network SSID (name)
char pass[] = "Fernet1845";              // your network password

// Button Input + LED Output


WiFiUDP Udp;                           // A UDP instance to let us send and receive packets over UDP
const IPAddress destIp(192,168,1,196);   // remote IP of the target device
const unsigned int destPort = 9000;    // remote port of the target device where the NodeMCU sends OSC to
const unsigned int localPort = 8000;   // local port to listen for UDP packets at the NodeMCU (another device must send OSC messages to this port)


String inData;


void setup() {
    
    Serial.begin(115200);
     // Open serial communications and wait for port to open:
    while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
    }
    Serial.println("NoeMCU OSC");
    // set the data rate for the SoftwareSerial port
    mySerial.begin(9600); 


    
     // Specify a static IP address
     // If you erase this line, your ESP8266 will get a dynamic IP address
     WiFi.config(IPAddress(192,168,1,123),IPAddress(192,168,1,1), IPAddress(255,255,255,0)); 
  
    // Connect to WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Starting UDP");
    Udp.begin(localPort);
    Serial.print("Local port: ");
    Serial.println(Udp.localPort());
}

void loop() {
   
   
    if (mySerial.available())
    {
            int data = mySerial.read();

            Serial.print("NodeMCU Received: ");
            Serial.println(data);

             // read btnInput and send OSC
            OSCMessage msgOut("/PoleTennis");
            msgOut.add(data);
            
            Udp.beginPacket(destIp, destPort);
            msgOut.send(Udp);
            Udp.endPacket();
            msgOut.empty();
            delay(10); // this delay could be shorter

        }

}
