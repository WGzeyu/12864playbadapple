int lpin[12]={ 5, 4, 3, 2,
               9, 8, 7, 6,
              14,15,16,17};
void setup() {
  // put your setup code here, to run once:
  for (int i=0; i<12 ;i++)
  {
    pinMode(lpin[i],OUTPUT);
    digitalWrite(lpin[i], HIGH);
    delay(100);
    digitalWrite(lpin[i], LOW);
  }
  delay(200);
  for (int i=0; i<12 ;i++)
  {
    digitalWrite(lpin[i], HIGH);
  }
  Serial.begin(2000000,SERIAL_8O1);
}
void loop() {
  // put your main code here, to run repeatedly:
  short weishu = 0;
  if(Serial.available()==12)
  {
    while (Serial.available()>0)
    {
      if(byte(Serial.read())==0)
      {
        digitalWrite(lpin[weishu++], LOW);
      }
      else
      {
        digitalWrite(lpin[weishu++], HIGH);
      }
    }
  }
}
