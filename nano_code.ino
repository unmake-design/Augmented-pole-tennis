// ToDo
// Implement MPU6050 with data from the DMP example
// check internet for posibility to increase the baud rate for Software Serial
// clean code for serial prints in loop

#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 8); // RX, TX

void setup()  
{
 // Open serial communications and wait for port to open:
 Serial.begin(115200);
 while (!Serial) {
   ; // wait for serial port to connect. Needed for Leonardo only
 }


 Serial.println("Nano");

 // set the data rate for the SoftwareSerial port
 mySerial.begin(9600);
}

void loop() // run over and over
{
  int data = (int) random(0,279);
  mySerial.write(data);
  Serial.println(data);
  delay(50);
}
