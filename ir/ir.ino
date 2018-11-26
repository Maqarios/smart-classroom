



#include <TimeLib.h>
#include <Time.h>
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

#define buzzer_pin 36

//--------------DOOR SENSORS VARIABLES-----------------------------------
int peopleCounter = 0;

int sensorPinIN = A0; 
int sensorPinOUT = A1; 
int sensorValueIN = 0; 
int sensorValueOUT = 0; 
int counter=0; 
int distanceSensorIN=0; 
int distanceSensorOUT=0;

unsigned long timerIN = 0; 
unsigned long timerOUT = 0;

char buf[100];
//----------------------------------------------------------------------

int student1x1, student1x2, student1x3, student2x1, student2x2, student2x3;

int led1x1, led1x2, led2x1, led2x2;

int start_hour=13;
int start_minutes=50;
int start_seconds=0;
int current_hour;
int current_minutes;
int current_seconds; 
int duration_hours=0;
int duration_minutes=0;
int duration_seconds=5;

bool timer_mode=false;
bool not_exam_mode=true;
unsigned long lastTick = 0;

void setup() {
  // put your setup code here, to run once:

    Serial.begin(9600);
  pinMode(sensorPinIN,INPUT);
  pinMode(sensorPinOUT,INPUT);

  
  
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

  
  setTime(13,50,00,19,11,2018);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void door_sensors()
{

 //take analog input from both door sensors
   sensorValueIN = analogRead(sensorPinIN);
   sensorValueOUT = analogRead(sensorPinOUT);

//---------------------------INNER SENSOR CONDITION--------------
   //If Voltage for the Inner sensor is betweem 400 and 700 
   if(sensorValueIN >=400 and sensorValueIN<700)
       {
                //print the voltage
            Serial.println(sensorValueIN);
                //add some delay to slow down the readings when a student passes
            delay(2000);
                // get the timing at which the student entered/cut the sensor
            timerIN = millis();

               
            if(timerIN>timerOUT)
               {        
                     peopleCounter++;
                     sprintf(buf, "Counter: %i", peopleCounter);
                     Serial.println(buf);
               }               
       }
//---------------------------OUTER SENSOR CONDITION-----
     //If Voltage for the Outer sensor is betweem 400 and 700 
    if(sensorValueOUT >=400 and sensorValueOUT<700)
      { 
              
             Serial.println( sensorValueOUT);
             delay(2000);
             timerOUT = millis();


            //if the timing of the outer sensor is greater than the timing of the inner one, that means that the student is leaving the classroom and the counter should be decremented
            if(timerIN<timerOUT)
               {       
                peopleCounter--;     
                sprintf(buf, "Counter: %i", peopleCounter);
                Serial.println(buf); 
                
               }                 

     }

  
} // end of the door method
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void display_duration(int hour,int mins,int sec){
 display.fillScreen(BLACK);
  display.setCursor(0, 0);
 display.setTextColor(WHITE);
 display.setTextSize(2);
 if(hour<10)
 display.print(0);
 display.print(hour);
 display.print(":");
  if(mins<10)
 display.print(0);
 display.print(mins);
 display.print(" ");
 display.setTextSize(1);
  if(sec<10)
 display.print(0);
 display.print(sec); 
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void reset_timer_mode(){
  timer_mode=false;
    digitalWrite(buzzer_pin, 1);
    delay(1000);
    digitalWrite(buzzer_pin, 0);
  
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void exam_mode(){
    current_hour=hour();
 current_minutes=minute();
 current_seconds=second();
 if(!timer_mode){
  if(current_hour==start_hour){
    if(current_minutes==start_minutes){
      if(current_seconds==start_seconds){
        timer_mode=true;
        //timer.in(duration_total_seconds*1000, reset_timer_mode);
      }
    }
  }
 }else{

  if(duration_seconds>0){
    if(millis() - lastTick >=1000){
      lastTick = millis();
      duration_seconds--;
      display_duration(duration_hours,duration_minutes,duration_seconds);
    }
  }
  if(duration_minutes>0){
    if(duration_seconds<=0){
      duration_minutes--;
      duration_seconds=60;
     

    }
  }
  if(duration_hours >0){
    if(duration_minutes<=0){
      duration_hours--;
      duration_minutes=60;
     
    }
  }

  if(duration_hours<=0 && duration_minutes<=0 && duration_seconds<=0){
    
    reset_timer_mode();
  
  }
 }
  
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void displayNotExamMode() {
  int shift = 46;
  for(int i = people; i > 0; i /= 10) {
    shift -= 4;
  }

  display.setCursor(shift, 0);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  

  display.fillRect(0,27, 8, 8, student1x1 ? RED : BLACK);
  display.fillRect(46,27, 8, 8, student1x2 ? RED : BLACK);
  display.fillRect(88,27, 8, 8, student1x3 ? RED : BLACK);
  display.fillRect(0,48, 8, 8, student2x1 ? RED : BLACK);
  display.fillRect(46,48, 8, 8, student2x2 ? RED : BLACK);
  display.fillRect(88,48, 8, 8, student2x3 ? RED : BLACK);
}
//---------------------------------------LOOP-------------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() {
  // put your main code here, to run repeatedly:
  
  door_sensors();
  notExamMode();
  displayNotExamMode();

}
