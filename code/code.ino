int soil_moisture=analogRead(A0);  // read from analog pin A0
int water_pomp_relay = 13;

void setup()
{
  Serial.begin(9600);
  pinMode(water_pomp_relay , OUTPUT);
}

void loop()
{
  digitalWrite(water_pomp_relay , LOW);
  //TODO : write to LCD if Supposed to be
  Serial.print("analog value: ");
  Serial.println(soil_moisture);

  if(soil_moisture<30)
  {
    Serial.println("Dry soil");
    //TODO : write to LCD if Supposed to be
  }

  if((soil_moisture>300)&&(soil_moisture<700))
  {
    Serial.println("Humid soil");
    //TODO : write to LCD if Supposed to be
  }

  if((soil_moisture>700)&&(soil_moisture<950))
  {
    //TODO : write to LCD if Supposed to be
    Serial.println("water");
    digitalWrite(water_pomp_relay , HIGH);
  }
  delay(500);
}