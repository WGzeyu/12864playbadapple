int lpin[12]={ 5, 4, 3, 2,
               9, 8, 7, 6,
              14,15,16,17};
unsigned long lasttime[12]={};
boolean zhuangtai[12]={};
byte liangdu[12]={0,14,39,65,90,115,140,165,190,216,241,255};
short ltime = 10; //每个亮度值点亮多少微秒，数值越低，频率变高，可显示的亮度范围更窄；数值越高，频率变低，可显示的亮度范围更宽。
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
    digitalWrite(lpin[i], LOW);
  }
  Serial.begin(2000000,SERIAL_8O1);
}
void loop() {
  // put your main code here, to run repeatedly:
  pwm();
  short weishu = 0;
  if(Serial.available()==12)
  {
    while (Serial.available()>0)
    {
      pwm();
      liangdu[weishu++]=byte(Serial.read());
    }
  }
}
void pwm() {
  unsigned long ntime = micros();
  for (int i=0; i<12 ;i++)
  {
    if(zhuangtai[i]) //如果亮起
    {
      
      if(liangdu[i]!=255 && ntime-lasttime[i]>=liangdu[i]*ltime)
      {
        digitalWrite(lpin[i], LOW);
        lasttime[i]=micros();
        ntime=lasttime[i];
        zhuangtai[i]=false;
      }
    }
    else //否则(没有亮起)
    {
      if(liangdu[i]!=0 && ntime-lasttime[i]>=(255-liangdu[i])*ltime)
      {
        digitalWrite(lpin[i], HIGH);
        lasttime[i]=micros();
        ntime=lasttime[i];
        zhuangtai[i]=true;
      }
    }
  }
}
