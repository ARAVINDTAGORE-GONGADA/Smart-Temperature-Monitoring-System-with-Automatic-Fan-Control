const int tempPin = A0;   
const int motorPin = 9;  
void setup()
{
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int sensorValue = analogRead(tempPin);
  float voltage = sensorValue * (5.0 / 1023.0);

  float temperature = (voltage - 0.5) * 100.0;

  int pwmValue;
  if (temperature < 27.0)
  {
    pwmValue = 0;
  }
  else if (temperature >= 40.0)
  {
    pwmValue = 255;
  }
  else
  {
    pwmValue = (int)((temperature - 27.0)
                     * 255.0 / (40.0 - 27.0));
  }
  analogWrite(motorPin, pwmValue);
  Serial.print("Temp: ");
  Serial.print(temperature, 1);
  Serial.print("C, PWM: ");
  Serial.println(pwmValue);
  delay(500);
}