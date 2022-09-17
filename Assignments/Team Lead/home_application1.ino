int temp = A0;
void setup() {
  Serial.begin(9600);
  pinMode(7,OUTPUT);
  pinMode(4,INPUT);
  pinMode(11,OUTPUT);
  
}

void loop() {
  int temp_adc_val;
  float temp_val;
  int pir=digitalRead(4);
  
  temp_adc_val = analogRead(temp);
  temp_val = (temp_adc_val * 4.88);	
  temp_val = ((temp_val/10)-50);
  Serial.print(" Degree Celsius\n");
  Serial.print(temp_val);
  if(temp_val>=25 && pir==1)
  {
    digitalWrite(11,HIGH);
    digitalWrite(7,HIGH);
    Serial.println("fanON"); 
  }
  else
  {
    digitalWrite(11,LOW);
    digitalWrite(7,LOW);
    Serial.println("fan OFF");
  }
}
