#include <U8g2lib.h>
#include <U8x8lib.h>
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0,5,6,7,13);
uint8_t apple[704] = {};
void setup() {
  Serial.begin(115200);
  u8g2.begin();
}
void loop() {
  short weishu = 0;
  if(Serial.available()==704) //88*64/8=704
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
  }
  else if(Serial.available()>704)
  {
    Serial.flush();
  }
}
