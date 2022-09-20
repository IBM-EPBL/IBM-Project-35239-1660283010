int LED = A1;
const int gas = 0;
int MQ2pin = A0;


void setup() {
  Serial.begin(9600);
  pinMode(4,OUTPUT);
}

void loop() {
  const int lm35_pin = A2;
  float sensorValue,MQ2pin;
  sensorValue = analogRead(MQ2pin); // read analog input pin 0
 
  int temp_adc_val;
  float temp_val;
  temp_adc_val = analogRead(lm35_pin);
  temp_val = (temp_adc_val *4.88);	
  temp_val = ((temp_val/10)-50);
  
  if(sensorValue >= 470 && temp_val>=32){
    digitalWrite(LED,HIGH);
    Serial.print(sensorValue);
    Serial.println(" |SMOKE DETECTED AND TEMP IS HIGH");
    digitalWrite(4,HIGH);
    
    Serial.print("Temperature = ");
    Serial.print(temp_val);
  
  }
  else{
  	digitalWrite(LED,LOW);
    Serial.println("Sensor Value: ");
    Serial.println(sensorValue);
    Serial.print("Temperature = ");
   Serial.print(temp_val);
    digitalWrite(4,LOW);
  } 
  delay(1000);
}
	float getsensorValue(int pin){
  	return (analogRead(pin));
}