//#include <timer.h>
//#include <Adafruit_GFX.h>
//#include <gfxfont.h>
//#include <Adafruit_SSD1331.h>
//#include <SPI.h>
//#define sclk 52
//#define mosi 51
//#define cs   47
//#define rst  49
//#define dc   48
//// Color definitions
//#define BLACK           0x0000
//#define BLUE            0x001F
//#define RED             0xF800
//#define GREEN           0x07E0
//#define CYAN            0x07FF
//#define MAGENTA         0xF81F
//#define YELLOW          0xFFE0  
//#define WHITE           0xFFFF
auto t = timer_create_default();
int interval=10000;
int helper =interval;
boolean timer_set1=true;
//Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, rst);
void setup(){
   display.begin();
  display.fillScreen(BLACK);
  Serial.begin(9600);
}
 bool doafter(void*){
  display.setCursor(0, 0);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.print(interval);
  return true;
 }

 bool doafter1(void*){
  display.fillscreen(BLACK);
  display.setCursor(0, 0);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  
  display.print(helper--);
  //helper=helper-1;
  return true;
 }
void loop() {
   
  t.tick();
  if(timer_set1 && interval>0){
  t.in(1000, doafter);
   t.in(1000,doafter1);
  }

//  display.setCursor(0, 0);
//  display.setTextColor(WHITE);
//  display.setTextSize(2);
//  interval=interval-t.tick();
//  display.print(interval);
}
