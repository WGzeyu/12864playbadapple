#include <ESP8266WiFi.h>
#include <U8g2lib.h>
#include <U8x8lib.h>
const char* ssid     = "WGzeyu_2.4G";
const char* password = "Hz3senxjUllrDYjaPZb5jr53lN6qdsgG";
short zhuangtai = 0;
uint8_t testb[704]={};
WiFiClient client;

//U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0,D0,D1,D2,D3);
U8G2_ST7920_128X64_1_HW_SPI u8g2(U8G2_R0,D2,D3); //左到右 5 7 2(CS) 3(不用接)

//U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_ALT0_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   // same as the NONAME variant, but may solve the "every 2nd line skipped" problem
//U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* reset=*/ 8);

void setup() {
  WiFi.begin(ssid, password);
  u8g2.begin();
}

void loop() {
  if(zhuangtai==0 && WiFi.status()==WL_CONNECTED)
  {
    zhuangtai=1;
    const int httpPort = 802;
    client.connect("192.168.2.138", httpPort);
  }
  while(client.available()){
    client.read(testb,704);
    u8g2.firstPage();
    do {
      u8g2.drawXBM(21,0, 86, 64, testb);
    } while (u8g2.nextPage());
  }
}
