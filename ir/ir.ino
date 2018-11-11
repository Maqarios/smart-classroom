// Pin Naming Convention: [Name] + [Row] +  x + [Column] + Pin
int student1x1Pin = 13;
int student1x2Pin = 12;
int student1x3Pin = 11;
int student2x1Pin = 10;
int student2x2Pin = 9;
int student2x3Pin = 8;

int led1x1Pin = 7;
int led1x2Pin = 6;
int led2x1Pin = 5;
int led2x2Pin = 4;

int student1x1, student1x2, student1x3, student2x1, student2x2, student2x3;
int led1x1, led1x2, led2x1, led2x2;

void setup() {
  // put your setup code here, to run once:

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
    led1x1 = led1x1 | student2x2;
    led2x1 = student2x2;
  }

  digitalWrite(led1x1Pin, led1x1);
  digitalWrite(led1x2Pin, led1x2);
  digitalWrite(led2x1Pin, led2x1);
  digitalWrite(led2x2Pin, led2x2);
}

void loop() {
  // put your main code here, to run repeatedly:
}
