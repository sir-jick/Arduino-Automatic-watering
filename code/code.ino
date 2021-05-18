
int water_pomp_relay = 13;

void setup()
{
  Serial.begin(9600);
  pinMode(water_pomp_relay , OUTPUT);
}

void loop()
{
  int soil_moisture=analogRead(A0);  // read from analog pin A0
  digitalWrite(water_pomp_relay , LOW);
  //TODO : write to LCD if Supposed to be
  Serial.print("analog value: ");
  Serial.println(soil_moisture);

  if(soil_moisture<30)
  {
    Serial.println("Dry soil");
    //TODO : write to LCD if Supposed to be
    digitalWrite(water_pomp_relay,1);
    delay(3000);
  }

  if((soil_moisture>300)&&(soil_moisture<700))
  {
    Serial.println("Humid soil");
    //TODO : write to LCD if Supposed to be
    digitalWrite(water_pomp_relay,0);
  }

  if((soil_moisture>700)&&(soil_moisture<950))
  {
    //TODO : write to LCD if Supposed to be
    Serial.println("watering");
    digitalWrite(water_pomp_relay , HIGH);
  }
  delay(500);
}