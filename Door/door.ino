
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

void setup() 
{
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  pinMode(sensorPinIN,INPUT);
  pinMode(sensorPinOUT,INPUT);

}


void loop() 
{
  // put your main code here, to run repeatedly:

   sensorValueIN = analogRead(sensorPinIN);
   sensorValueOUT = analogRead(sensorPinOUT);

   if(sensorValueIN >=400 and sensorValueIN<700)
       {
                
            Serial.println(sensorValueIN);
            delay(2000);
            timerIN = millis();
           
            if(timerIN>timerOUT)
               {        
                     counter++;
                     sprintf(buf, "Counter: %i", counter);
                     Serial.println(buf);
               }               
       }

    if(sensorValueOUT >=400 and sensorValueOUT<700)
      { 
              
            Serial.println( sensorValueOUT);
            delay(2000);
            timerOUT = millis();
            
            if(timerIN<timerOUT)
               {       
                counter--;     
                sprintf(buf, "Counter: %i", counter);
                Serial.println(buf); 
                
               }                 

     }


}
