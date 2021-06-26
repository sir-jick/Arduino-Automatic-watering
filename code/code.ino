#include <SoftwareSerial.h>

#define water_pomp_relay 13

String number = "+989381684220";
//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); 
//SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Initializing..."); 
  pinMode(water_pomp_relay , OUTPUT);
  delay(1000);
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS="+ number); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.println("system is ready to use "); //text content
  updateSerial();
  mySerial.write(26);
}

void loop()
{
  int soil_moisture=analogRead(A0);  // read from analog pin A0
  digitalWrite(water_pomp_relay , LOW);
  Serial.print("analog value: ");
  Serial.println(soil_moisture);

  if(soil_moisture<30)
  {
    Serial.println("Dry soil");
    digitalWrite(water_pomp_relay,HIGH);
    delay(3000);
    if(soil_moisture<30)
    {
      mySerial.print("the container is run out , check the water source"); //text content to send sms
      updateSerial();
      mySerial.write(26);
      delay(10000);
    }
  }

  if((soil_moisture>300)&&(soil_moisture<700))
  {
    Serial.println("Humid soil");
    Serial.println("watering");
    mySerial.println("the system is watering now"); //text content to send sms
    updateSerial();
    mySerial.write(26);
    digitalWrite(water_pomp_relay , HIGH);
    delay(1500);
  }

  if((soil_moisture>700)&&(soil_moisture<950))
  {
    digitalWrite(water_pomp_relay,0);
    mySerial.println("no need to watering"); //text content to send sms
    updateSerial();
    mySerial.write(26);
  }
  delay(1000); // TODO : *3600 repeat until every 1 hour
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available())
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
