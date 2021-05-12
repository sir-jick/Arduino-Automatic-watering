void setup(){

Serial.begin(9600);
pinMode(13, OUTPUT);
}

void loop(){
digitalWrite(13, LOW);
int soil_moisture=analogRead(A0);  // read from analog pin A3

Serial.print("analog value: ");
Serial.println(soil_moisture);

if(soil_moisture<30) {

Serial.println("Dry soil");

}

if((soil_moisture>300)&&(soil_moisture<700)) {

Serial.println("Humid soil");

}

if((soil_moisture>700)&&(soil_moisture<950)){
  Serial.println("water");
  digitalWrite(13, HIGH);
  }
    delay(500);
}