#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

#define sclk 52
#define mosi 51
#define cs   47
#define rst  49
#define dc   48

// Color definitions
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, rst);

// Pin Naming Convention: <Type> + <Row> +  "x" + <Column> + "Pin"
#define student1x1Pin 46
#define student1x2Pin 45
#define student1x3Pin 44
#define student2x1Pin 43
#define student2x2Pin 42
#define student2x3Pin 41

#define led1x1Pin 40
#define led1x2Pin 39
#define led2x1Pin 38
#define led2x2Pin 37

int people = 0;

int student1x1, student1x2, student1x3, student2x1, student2x2, student2x3;
int led1x1, led1x2, led2x1, led2x2;

void setup() {
  // put your setup code here, to run once:

  display.begin();
  display.fillScreen(BLACK);

  pinMode(student1x1Pin, INPUT);
  pinMode(student1x2Pin, INPUT);
  pinMode(student1x3Pin, INPUT);
  pinMode(student2x1Pin, INPUT);
  pinMode(student2x2Pin, INPUT);
  pinMode(student2x3Pin, INPUT);

  pinMode(led1x1Pin, OUTPUT);
  pinMode(led1x2Pin, OUTPUT);
  pinMode(led2x1Pin, OUTPUT);
  pinMode(led2x2Pin, OUTPUT);
}

void notExamMode() {
  student1x1 = !digitalRead(student1x1Pin);
  student1x2 = !digitalRead(student1x2Pin);
  student1x3 = !digitalRead(student1x3Pin);
  student2x1 = !digitalRead(student2x1Pin);
  student2x2 = !digitalRead(student2x2Pin);
  student2x3 = !digitalRead(student2x3Pin);

  led1x1 = 0;
  led1x2 = 0;
  led2x1 = 0;
  led2x2 = 0;

  // Left
  led1x1 = student1x1 | student2x1;
  led2x1 = student2x1;

  // Right
  led1x2 = student1x3 | student2x3;
  led2x2 = student2x3;

  // Middle
  if (!led1x1 & !led1x2)
    led1x1 = student1x2;
  if (!led2x1 & !led2x2) {
    if(led1x2) {
      led2x2 = student2x2;
    } else {
      led1x1 = led1x1 | student2x2;
      led2x1 = student2x2;
    }
  }

  digitalWrite(led1x1Pin, led1x1);
  digitalWrite(led1x2Pin, led1x2);
  digitalWrite(led2x1Pin, led2x1);
  digitalWrite(led2x2Pin, led2x2);
}

void displayNotExamMode() {
  int shift = 46;
  for(int i = people; i > 0; i /= 10) {
    shift -= 4;
  }

  display.setCursor(shift, 0);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.print(people);

  display.fillRect(0,27, 8, 8, student1x1 ? RED : BLACK);
  display.fillRect(46,27, 8, 8, student1x2 ? RED : BLACK);
  display.fillRect(88,27, 8, 8, student1x3 ? RED : BLACK);
  display.fillRect(0,48, 8, 8, student2x1 ? RED : BLACK);
  display.fillRect(46,48, 8, 8, student2x2 ? RED : BLACK);
  display.fillRect(88,48, 8, 8, student2x3 ? RED : BLACK);
}

void loop() {
  // put your main code here, to run repeatedly:
  notExamMode();
  displayNotExamMode();
}
