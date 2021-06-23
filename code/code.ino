#include <SoftwareSerial.h>

#define water_pomp_relay 13

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(water_pomp_relay , OUTPUT);
}

void loop()
{
  
  int soil_moisture=analogRead(A0);  // read from analog pin A0
  digitalWrite(water_pomp_relay , LOW);
  //TODO : send SMS if Supposed to be
  Serial.print("analog value: ");
  Serial.println(soil_moisture);

  if(soil_moisture<30)
  {
    Serial.println("Dry soil");
    //TODO : send SMS if Supposed to be
    digitalWrite(water_pomp_relay,HIGH);
    delay(3000);
    if(soil_moisture<30)
    {
      send_sms("the container is out of water, please check the water source"); // TODO : change this function with right thing
      delay(10000);
    }
  }

  if((soil_moisture>300)&&(soil_moisture<700))
  {
    Serial.println("Humid soil");
    //TODO : send send_sms if Supposed to be
    Serial.println("watering");
    send_sms("the system is watering now"); // TODO : change this function with right thing
    digitalWrite(water_pomp_relay , HIGH);
    delay(1000);
  }

  if((soil_moisture>700)&&(soil_moisture<950))
  {
    //TODO : send send_sms if Supposed to be

    digitalWrite(water_pomp_relay,0);
    send_sms("no need to watering ,I am not thirsty") // TODO : change this function with right thing
  }
  delay(3600*1000); // repeat until every 1 hour
}