#include <U8g2lib.h>
#include <U8x8lib.h>
//U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0,5,6,7,13); //软SPI比硬SPI在显示86*64位图时慢2ms
U8G2_ST7920_128X64_1_HW_SPI u8g2(U8G2_R0,10,8); //左到右 13 11 10(CS) 8(不用接)
uint8_t apple[704] = {};
void setup() {
  Serial.begin(2000000,SERIAL_8O1);
  u8g2.begin();
}
void loop() {
  short weishu = 0;
  if(Serial.available()==704) //88*64/8=704 注意！编译前需将串口缓冲区改为706字节
  {
    while (Serial.available()>0)  
    {
      apple[weishu++] = char(Serial.read());
      if(weishu==704)
      {
        weishu=0;
        u8g2.firstPage();
        do {
          u8g2.drawXBM(21,0, 86, 64, apple);
        } while (u8g2.nextPage());
      }
    }
    //Serial.flush();
    while(Serial.read()>= 0){}
  }
  else if(Serial.available()>704)
  {
    //Serial.flush();
    while(Serial.read()>= 0){}
  }
}
