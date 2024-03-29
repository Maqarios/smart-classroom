#include <TimeLib.h>
#include <Time.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include <stdio.h>
#include <string.h>

#define sclk 52
#define mosi 51
#define cs 47
#define rst 49
#define dc 48
// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

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

#define buzzer_pin 36

int student1x1, student1x2, student1x3, student2x1, student2x2, student2x3;
int led1x1, led1x2, led2x1, led2x2;
int prevPeopleCounter, peopleCounter;

int start_hour = 0;
int start_minute = 0;
int start_second = 0;
int current_hour;
int current_minute;
int current_second;
int duration_hour = 0;
int duration_minute = 0;
int duration_second = 0;
bool sent_signal = false;
bool started_exam = false;
unsigned long lastTick = 0;

void display_duration(int hours, int mins, int secs)
{
  display.fillScreen(BLACK);
  display.setCursor(0, 0);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  if (hours < 10)
    display.print(0);
  display.print(hours);
  display.print(":");
  if (mins < 10)
    display.print(0);
  display.print(mins);
  display.print(" ");
  display.setTextSize(1);
  if (secs < 10)
    display.print(0);
  display.print(secs);
  Serial.print(hours);
  Serial.print(" ");
  Serial.print(mins);
  Serial.print(" ");
  Serial.print(secs);
  Serial.println();
}

void reset_timer_mode()
{
  started_exam = false;
  sent_signal = false;
  digitalWrite(buzzer_pin, 1);
  delay(1000);
  digitalWrite(buzzer_pin, 0);
  display.fillScreen(BLACK);
  Serial.println("Finished exam, time to revise and cry for the rest of the day");
}

void exam_mode()
{
  current_hour = hour();
  current_minute = minute();
  current_second = second();
  if (!started_exam)
  {
    if (current_hour == start_hour)
    {
      if (current_minute == start_minute)
      {
        if (current_second == start_second)
        {
          started_exam = true;
          digitalWrite(led1x1Pin, 1);
          digitalWrite(led1x2Pin, 1);
          digitalWrite(led2x1Pin, 1);
          digitalWrite(led2x2Pin, 1);
          Serial.println("Exam started, getting my bags");
          //timer.in(duration_total_seconds*1000, reset_timer_mode);
        }
      }
    }
  }
  else
  {

    if (duration_second > 0)
    {
      if (millis() - lastTick >= 1000)
      {
        lastTick = millis();
        duration_second--;
        display_duration(duration_hour, duration_minute, duration_second);
      }
    }
    if (duration_minute > 0)
    {
      if (duration_second <= 0)
      {
        duration_minute--;
        duration_second = 60;
      }
    }
    if (duration_hour > 0)
    {
      if (duration_minute <= 0)
      {
        duration_hour--;
        duration_minute = 60;
      }
    }

    if (duration_hour <= 0 && duration_minute <= 0 && duration_second <= 0)
    {

      reset_timer_mode();
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void notExamMode()
{
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

  prevPeopleCounter = peopleCounter;
  peopleCounter = student1x1 + student1x2 + student1x3 + student2x1 + student2x2 + student2x3;

  // Left
  led1x1 = student1x1 | student2x1;
  led2x1 = student2x1;

  // Right
  led1x2 = student1x3 | student2x3;
  led2x2 = student2x3;

  // Middle
  if (!led1x1 & !led1x2)
    led1x1 = student1x2;
  if (!led2x1 & !led2x2)
  {
    if (led1x2)
    {
      led2x2 = student2x2;
    }
    else
    {
      led1x1 = led1x1 | student2x2;
      led2x1 = student2x2;
    }
  }

  digitalWrite(led1x1Pin, led1x1);
  digitalWrite(led1x2Pin, led1x2);
  digitalWrite(led2x1Pin, led2x1);
  digitalWrite(led2x2Pin, led2x2);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void displayNotExamMode()
{
  int shift = 46;
    for (int i = peopleCounter; i > 0; i /= 10)
    {
    shift -= 4;
  }

  if (prevPeopleCounter != peopleCounter)
    display.fillRect(0, 0, 100, 15, BLACK);
  display.setCursor(shift, 0);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.print(peopleCounter);
  display.fillRect(0, 27, 8, 8, student1x1 ? RED : GREEN);
  display.fillRect(46, 27, 8, 8, student1x2 ? RED : GREEN);
  display.fillRect(88, 27, 8, 8, student1x3 ? RED : GREEN);
  display.fillRect(0, 48, 8, 8, student2x1 ? RED : GREEN);
  display.fillRect(46, 48, 8, 8, student2x2 ? RED : GREEN);
  display.fillRect(88, 48, 8, 8, student2x3 ? RED : GREEN);
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
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
  pinMode(buzzer_pin, OUTPUT);
  delay(200);
  while (!Serial.available())
  {
    Serial.println("unavailable"); // wait until time setting string is received;
  }

  if (Serial.available())
  {
    String current_year = Serial.readStringUntil(':');
    String current_month = Serial.readStringUntil(':');
    String current_day = Serial.readStringUntil(':');
    String current_hour = Serial.readStringUntil(':');
    String current_minute = Serial.readStringUntil(':');
    String current_second = Serial.readStringUntil(':');
    setTime(current_hour.toInt(), current_minute.toInt(), current_second.toInt(), current_day.toInt(), current_month.toInt(), current_year.toInt());
  }

  Serial.println("done with setup");
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    String received_start_hour = Serial.readStringUntil(':');
    String received_start_minute = Serial.readStringUntil(':');
    String received_duration_hour = Serial.readStringUntil(':');
    String received_duration_minute = Serial.readStringUntil(':');
    Serial.println(received_start_hour + ":" + received_start_minute + "   " + received_duration_hour + ":" + received_duration_minute);
    start_hour = received_start_hour.toInt();
    start_minute = received_start_minute.toInt();
    duration_hour = received_duration_hour.toInt();
    duration_minute = received_duration_minute.toInt();
    sent_signal = true;
  }
  if (sent_signal)
  {
    //TODO: Add exam mode
    exam_mode();
  }

  if (!started_exam)
  {
    notExamMode();
    displayNotExamMode();
  }

}
