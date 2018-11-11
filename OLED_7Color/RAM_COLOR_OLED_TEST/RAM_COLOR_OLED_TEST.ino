#define sclk 13
#define mosi 11
#define cs   10
#define rst  9
#define dc   8

// Color definitions
#define  BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>


Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, rst);

void setup() {

  display.begin();
  display.fillScreen(RED);
  delay(300);
  display.fillScreen(GREEN);
  delay(300);
  display.fillScreen(BLUE);
  delay(300);
  display.fillScreen(BLACK);
  delay(1000);
  display.setCursor(20,5);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.print("R A M");

  display.setCursor(8,25);
  display.setTextColor(RED);
  display.setTextSize(1);
  display.print("Electronics");

  display.fillRect(10,40, 75, 20, RED);

  display.setCursor(20,47);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.print("Colors");

  display.drawRect(0,0,96,64,WHITE);
  delay(1000);
}

void loop() 
{
  display.fillRect(10,40, 75, 20, BLACK);
  delay(1000);
  display.fillRect(10,40, 75, 20, RED);
  display.setCursor(20,47);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.print("Welcome :)");
  delay(1000);
}

