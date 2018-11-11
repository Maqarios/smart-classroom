



void asd() {

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

void asd2() 
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
