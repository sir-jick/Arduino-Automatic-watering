#include <SoftwareSerial.h>

#define water_pomp_relay 13
#define led_auto_mode 5
#define led_manual_mode 6

#define sms true // TODO  : it is for testing verification do NOT forget to remove


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
  if(sms) // TODO : replace corect receive sms code for manual watering
  {
    digitalWrite(led_auto_mode, LOW);
    digitalWrite(led_manual_mode, HIGH);
    manual_watering();
  }
  else
  {
    digitalWrite(led_auto_mode, HIGH);
    digitalWrite(led_manual_mode, LOW);
    automatic_watering();
  }
  delay(3600*1000); // repeat until every 1 hour
}

void automatic_watering()
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
    digitalWrite(water_pomp_relay,1);
    delay(3000);
  }

  if((soil_moisture>300)&&(soil_moisture<700))
  {
    Serial.println("Humid soil");
    //TODO : send SMS if Supposed to be
    digitalWrite(water_pomp_relay,0);
  }

  if((soil_moisture>700)&&(soil_moisture<950))
  {
    //TODO : send SMS if Supposed to be
    Serial.println("watering");
    digitalWrite(water_pomp_relay , HIGH);
    delay(500);
  }
}
void manual_watering()
{
  Serial.println("manual watering");
  digitalWrite(water_pomp_relay , HIGH);
  delay(3000);
  digitalWrite(water_pomp_relay ,LOW);
}