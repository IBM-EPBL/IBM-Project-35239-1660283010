const int lm35_pin=A0;

void setup()
{
  pinMode(2,OUTPUT);
  pinMode(3,INPUT);
  pinMode(7,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(2,LOW);
  digitalWrite(2,HIGH);
  delayMicroseconds(10);
  digitalWrite(2,LOW);
  float dur=pulseIn(3,HIGH);
  float dis=(dur*0.034)/2;
  
  int temp_adc_val;
  float temp_val;
  temp_adc_val = analogRead(lm35_pin);
  temp_val = (temp_adc_val * 4.88);	
  temp_val = ((temp_val/10)-50);
  

 
  if(dis<=15 && 8<=dis)
  {
    Serial.print("temprature=");
    Serial.println(temp_val);
    digitalWrite(4,HIGH);
    if(temp_val>38)
    {
    digitalWrite(7,HIGH);
    }
    digitalWrite(7,LOW);
  }
  else
  {
    Serial.println("keep distance in 8cm to 15cm");
    digitalWrite(4,LOW);
    digitalWrite(7,LOW);
  }
  
  delay(1000);
}